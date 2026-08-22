/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputValidation.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 16:42:30 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/22 17:07:35 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <exception>
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>

std::string   trim(std::string const& s)
{
	std::string::size_type  start = s.find_first_not_of(" \t\r");

	if (start == std::string::npos)
			return ("");
	std::string::size_type  end = s.find_last_not_of(" \t\r");
	return (s.substr(start, end - start + 1));
}

static int checkYear(std::string const& date)
{
	std::string			year = date.substr(0, 4);
	std::istringstream	ss(year);
	int					value;

	ss >> value;
	if (ss.fail() || !ss.eof())
		throw std::runtime_error("Error: bad input => " + date);
	if (value < 2009)
		throw std::runtime_error("Error: bad input => " + date);
	return (value);
}

static int checkMonth(std::string const& date)
{
	std::string			month = date.substr(5, 2);
	std::istringstream	ss(month);
	int					value;

	ss >> value;
	if (ss.fail() || !ss.eof())
		throw std::runtime_error("Error: bad input => " + date);
	if (value < 1 || value > 12)
		throw std::runtime_error("Error: bad input => " + date);
	return (value);
}

static void checkDay(std::string const& date, int month, int year)
{
	int	days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	std::string			day = date.substr(8, 2);
	std::istringstream	ss(day);
	int					value;

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		days[1] = 29;
	ss >> value;
	if (ss.fail() || !ss.eof())
		throw std::runtime_error("Error: bad input => " + date);
	if (value < 1 || value > days[month - 1])
		throw std::runtime_error("Error: bad input => " + date);
}

void validateDate(std::string const& date)
{
	int						year;
	int						month;

	if (date.size() != 10)
		throw std::runtime_error("Error: bad input => " + date);
	for (std::string::size_type i = 0; i < date.size(); i++)
	{
		if (i == 4 || i == 7)
		{
			if (date[i] != '-')
				throw std::runtime_error("Error: bad input => " + date);
		}
		else if (!std::isdigit(static_cast<unsigned char>(date[i])))
			throw std::runtime_error("Error: bad input => " + date);
	}
	year = checkYear(date);
	month = checkMonth(date);
	checkDay(date, month, year);
}
