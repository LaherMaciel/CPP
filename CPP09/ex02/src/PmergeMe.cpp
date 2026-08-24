/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 19:05:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/22 21:55:30 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <stdexcept>
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <sys/time.h>

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(PmergeMe const& other)
	: _vector(other._vector), _deque(other._deque) {}

PmergeMe::~PmergeMe(void) {}

PmergeMe&	PmergeMe::operator=(PmergeMe const& other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_deque = other._deque;
	}
	return (*this);
}

// One token -> one int. Digits only: no sign at all, not even '+'.
// Leading zeros are fine ("007" is 7). Zero itself is accepted -- the subject
// calls 0 part of "a positive integer" in ex00 (p.179).
// istringstream sets failbit past INT_MAX, so overflow is caught here.
int	parseToken(std::string const& token)
{
	std::string::size_type	i = 0;
	int						value;

	if (token.empty())
		throw std::runtime_error("Error");
	while (i < token.size())
	{
		if (!std::isdigit(static_cast<unsigned char>(token[i])))
			throw std::runtime_error("Error");
		i++;
	}

	std::istringstream	ss(token);
	
	ss >> value;
	if (ss.fail() || !ss.eof())
		throw std::runtime_error("Error");
	return (value);
}

// gettimeofday is POSIX -- present on Linux and macOS alike, no #ifdef needed.
// Wall-clock microseconds since the epoch, as a double so the subtraction
// below cannot lose the sub-second part.
double	nowMicroseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (static_cast<double>(tv.tv_sec) * 1000000.0
		+ static_cast<double>(tv.tv_usec));
}

void	printTime(std::string const& name, std::size_t count, double us)
{
	std::cout << "Time to process a range of " << count
		<< " elements with std::" << name << " : "
		<< std::fixed << std::setprecision(5) << us << " us" << std::endl;
}
