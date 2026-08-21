/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/20 16:43:34 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <algorithm>
#include <climits>

Span::Span(void)
{
	_maxSize = 0;
}

Span::Span(unsigned int n)
{
	_maxSize = n;
}

Span::Span(Span const& other)
{
	_maxSize = other._maxSize;
	_numbers = other._numbers;
}

Span::~Span(void)
{
}

Span&	Span::operator=(Span const& other)
{
	if (this == &other)
		return (*this);
	_numbers = other._numbers;
	_maxSize = other._maxSize;
	return (*this);
}

void	Span::addNumber(int number)
{
	if (_numbers.size() < _maxSize)
		_numbers.push_back(number);
	else
		throw OutOfBoundsException();
}

unsigned int	Span::shortestSpan(void) const
{
	unsigned int	currentSize = _numbers.size();
	unsigned int	shortestSpan = UINT_MAX;
	unsigned int	gap;

	if (currentSize < 2)
		throw OutOfBoundsException();
	std::vector<int>	sorted(_numbers);

	std::sort(sorted.begin(), sorted.end());
	for (unsigned int i = 0; i < currentSize - 1; i++)
	{
		gap = static_cast<unsigned int>(sorted[i + 1])
			- static_cast<unsigned int>(sorted[i]);
		if (gap < shortestSpan)
			shortestSpan = gap;
	}
	return (shortestSpan);
}

unsigned int	Span::longestSpan(void) const
{
	unsigned int	currentSize = _numbers.size();

	if (currentSize < 2)
		throw OutOfBoundsException();
	std::vector<int>::const_iterator min =
		std::min_element(_numbers.begin(), _numbers.end());
	std::vector<int>::const_iterator max =
		std::max_element(_numbers.begin(), _numbers.end());
	return (static_cast<unsigned int>(*max) -
	static_cast<unsigned int>(*min));
}

const char *Span::OutOfBoundsException::what() const throw()
{
	return ("Span: Out Of Bounds");
}
