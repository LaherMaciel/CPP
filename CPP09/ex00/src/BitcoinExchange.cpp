/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 18:40:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/22 18:03:57 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


#include <exception>
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cfloat>
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

static double	checkValue(std::string const& rate, double maxValue)
{
	std::istringstream	ss(rate);
	double				value;

	ss >> value;
	if (ss.fail() || !ss.eof())
		throw std::runtime_error("Error: bad input => " + rate);
	if (value < 0)
		throw std::runtime_error("Error: not a positive number.");
	if (value > maxValue)
		throw std::runtime_error("Error: too large a number.");
	return (value);
}

static bool	isCsvHeaderLine(std::string const& line)
{
	return (trim(line) == "date,exchange_rate");
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
	while (std::getline(f, line))
	{
		if (trim(line).empty() || isCsvHeaderLine(line))
			continue ;
		pos = line.find(',');
		if (pos == std::string::npos)
			throw std::runtime_error("Error: bad input => " + line);
		date = trim(line.substr(0, pos));
		validateDate(date);
		rate = trim(line.substr(pos + 1));
		value = checkValue(rate, DBL_MAX);
		_rates[date] = value;
	}
	if (_rates.empty())
		throw std::runtime_error("Error: the database is empty.");
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

static std::string::size_type getPosition(std::string const& line)
{
	std::string::size_type pos = line.find('|');
	if (pos == std::string::npos)
		throw std::runtime_error("Error: bad input => " + line);
	return (pos);
}

// The subject's input file opens with a "date | value" header.
// The CPP09 guide says to skip it, so it is skipped wherever it appears.
static bool	isHeaderLine(std::string const& line)
{
	return (trim(line) == "date | value");
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
	while (std::getline(f, line))
	{
		if (isHeaderLine(line))
			continue ;
		try
		{
			pos = getPosition(line);
			date = trim(line.substr(0, pos));
			validateDate(date);
			rate = trim(line.substr(pos + 1));
			value = checkValue(rate, 1000);
			btc_value = value * getRate(date);
			std::cout <<  std::setprecision(10) << date << " => " << value
				<< " = " << btc_value << std::endl;
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
