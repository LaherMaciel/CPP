/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/20 16:19:14 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <exception>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <climits>

void callShortestSpan(Span const &sp)
{
	try
	{
		std::cout << sp.shortestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void callLongestSpan(Span const &sp)
{
	try
	{
		std::cout << sp.longestSpan() << std::endl << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

int	main(void)
{
	Span	sp = Span(5);

	std::cout << "empty span" << std::endl;
	callShortestSpan(sp);
	callLongestSpan(sp);
	std::cout << std::endl;

	std::cout << "span with 1 value" << std::endl;
	sp.addNumber(6);
	callShortestSpan(sp);
	callLongestSpan(sp);
	std::cout << std::endl;

	std::cout << "span with 2 values" << std::endl;
	sp.addNumber(3);
	callShortestSpan(sp);
	callLongestSpan(sp);
	std::cout << std::endl;

	std::cout << "span with 5 values" << std::endl;
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	callShortestSpan(sp);
	callLongestSpan(sp);
	std::cout << std::endl;

	std::cout << "trying to add a 6th value" << std::endl;
	try
	{
		sp.addNumber(14);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "Copy and Assignment constructor test" << std::endl;
	Span	a = Span(5);

	a.addNumber(2);
	a.addNumber(101);

	Span	b(a);
	b.addNumber(52);

	Span	c(1);
	c = a;
	c.addNumber(50);

	std::cout << "Span a" << std::endl;
	callShortestSpan(a);
	callLongestSpan(a);
	std::cout << "Span b" << std::endl;
	callShortestSpan(b);
	callLongestSpan(b);
	std::cout << "Span c" << std::endl;
	callShortestSpan(c);
	callLongestSpan(c);
	std::cout << std::endl;

	std::cout << "Creating and adding a 10k+ Span" << std::endl;
	std::vector<int>	source(10526);

	std::generate(source.begin(), source.end(), std::rand);
	source[0] = INT_MIN;
	Span  big(10530);

	big.addNumber(INT_MAX);
	big.addRange(source.begin(), source.end());

	callShortestSpan(big);
	callLongestSpan(big);
	std::cout << std::endl;

	std::cout << "Trying to overfill the Span" << std::endl;
	try
	{
		Span sp4(3);

		sp4.addRange(source.begin(), source.end());
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
