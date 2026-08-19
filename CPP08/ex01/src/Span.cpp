/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/18 21:00:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <algorithm>

// Every body below is yours.

Span::Span(void)
{
}

Span::Span(unsigned int n)
{
	(void)n;
}

Span::Span(Span const& other)
{
	(void)other;
}

Span::~Span(void)
{
}

Span&	Span::operator=(Span const& other)
{
	(void)other;
	return (*this);
}

void	Span::addNumber(int number)
{
	(void)number;
}

int		Span::shortestSpan(void) const
{
	return (0);
}

int		Span::longestSpan(void) const
{
	return (0);
}
