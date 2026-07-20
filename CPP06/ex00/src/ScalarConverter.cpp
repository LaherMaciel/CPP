/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:58:53 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/07/13 20:54:10 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <cmath>
#include <string>
#include <iostream>
#include <cstring>
#include <climits>
#include <cctype>
#include <cstdlib>
#include <sstream>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter&) {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) { return (*this); }
ScalarConverter::~ScalarConverter() {}

static bool	isPseudo(const std::string& literal)
{
	const std::string	words[6] = {"nan", "nanf", "+inf", "-inf", "+inff", "-inff"};

	for (int i = 0; i < 6; i++)
			if (literal == words[i])
					return (true);
	return (false);
}

static void	printPseudo(std::string literal)
{
	if (literal == "nanf" || literal == "+inff" || literal == "-inff")
		literal = literal.substr(0, literal.length() - 1);
	std::cout << "char: impossible" << std::endl
		<< "int: impossible" << std::endl
		<< "float: " << literal << "f" << std::endl
		<< "double: " << literal << std::endl;
}

static bool isValidLiteral(std::string literal)
{
	char	*end;

	if (literal.empty())
		return (false);
	strtod(literal.c_str(), &end);
	if (end[0] == '\0' || strcmp(end, "f") == 0)
		return (true);
	return (false);
}

static void PrintImpossible()
{
	std::cout << "Invalid input!" << std::endl;
}

static void	printChar(double value)
{
	if (value != value || value < 0 || value > 127)
			std::cout << "char: impossible" << std::endl;
	else if (!isprint(static_cast<char>(value)))
			std::cout << "char: Non displayable" << std::endl;
	else
			std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
}

static void	printInt(double value)
{
	if (value != value || value > INT_MAX || value < INT_MIN)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(value) << std::endl;
}

static void	printFloat(double value)
{
	float					f;
	std::ostringstream	oss;

	f = static_cast<float>(value);
	oss << f;
	std::cout << "float: " << oss.str();
	if (oss.str().find('.') == std::string::npos
			&& oss.str().find('e') == std::string::npos
			&& f == f && f != HUGE_VALF && f != -HUGE_VALF)
		std::cout << ".0";
	std::cout << "f" << std::endl;
}

static void	printDouble(double value)
{
	std::ostringstream	oss;

	oss << value;
	std::cout << "double: " << oss.str();
	if (oss.str().find('.') == std::string::npos
		&& oss.str().find('e') == std::string::npos
		&& value == value && value != HUGE_VAL && value != -HUGE_VAL)
		std::cout << ".0";
	std::cout << std::endl;
}

void	ScalarConverter::convert(const std::string& literal)
{
	char	*end;
	double	value;

	if (isPseudo(literal))
		return (printPseudo(literal));
	if (literal.length() == 1 && !isdigit(literal[0]) && isprint(literal[0]))
	{
		value = literal[0];
		printChar(value); printInt(value); printFloat(value); printDouble(value);
		return ;
	}
	if (!isValidLiteral(literal))
		return (PrintImpossible());
	value = strtod(literal.c_str(), &end);
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}
