/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 18:40:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/21 22:01:30 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


#include <exception>
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& other)
{
	_rates = other._rates;
}

BitcoinExchange::~BitcoinExchange(void) {}

BitcoinExchange&	BitcoinExchange::operator=(BitcoinExchange const& other)
{
	if (this != &other)
		_rates = other._rates;
	return (*this);
}

void	BitcoinExchange::loadDatabase(std::string const& path)
{
	std::ifstream			f(path.c_str());
	std::string				line;
	std::string::size_type	pos;
	std::string				date;
	std::string				rate;
	double					value;

	if (!f.is_open())
		throw std::runtime_error("Error: could not open file.");
	std::getline(f, line);
	while (std::getline(f, line))
	{
		pos = line.find(',');
		if (pos == std::string::npos)
			throw std::runtime_error("could not find ',' in: \"" + line + "\".");
		date = trim(line.substr(0, pos));
		rate = trim(line.substr(pos + 1));

		std::istringstream	ss(rate);
		ss >> value;
		if (ss.fail() || !ss.eof())
			throw std::runtime_error("bad Number");
		_rates[date] = value;
	}
}

double	BitcoinExchange::getRate(std::string const& date) const
{
	std::map<std::string, double>::const_iterator	it
		= _rates.lower_bound(date);

	if (it != _rates.end() && it->first == date)
		return (it->second);
	if (it == _rates.begin())
		throw std::runtime_error("Error: bad input => " + date);
	--it;
	return (it->second);
}

static double checkValue(std::string const& rate)
{
	std::istringstream	ss(rate);
	double				value;

	ss >> value;
	if (ss.fail() || !ss.eof())
		throw std::runtime_error("Error: bad input => " + rate);
	if (value < 0)
		throw std::runtime_error("Error: not a positive number.");
	if (value > 1000)
		throw std::runtime_error("Error: too large a number.");
	return (value);
}

static std::string::size_type getPosition(std::string const& line)
{
	std::string::size_type pos = line.find('|');
	if (pos == std::string::npos)
		throw std::runtime_error("Error: bad input => " + line);
	return (pos);
}

void	BitcoinExchange::processInput(std::string const& path)
{
	std::ifstream			f(path.c_str());
	std::string				line;
	std::string::size_type	pos;
	std::string				date;
	std::string				rate;
	double					value;
	double					btc_value;

	if (!f.is_open())
		throw std::runtime_error("Error: could not open file.");
	std::getline(f, line);
	while (std::getline(f, line))
	{
		try
		{
			pos = getPosition(line);
			date = trim(line.substr(0, pos));
			validateDate(date);
			rate = trim(line.substr(pos + 1));
			value = checkValue(rate);
			btc_value = value * getRate(date);
			std::cout <<  std::setprecision(10) << date << " => " << value
				<< " = " << btc_value << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}
