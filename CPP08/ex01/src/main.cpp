/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/18 21:00:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>

// The subject's own example. It must print exactly 2 then 14.
// "you will write your own tests, and they will be far more thorough than
//  the ones below. Test your Span with at least 10,000 numbers."

int	main(void)
{
	Span	sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	// TODO: a 6th addNumber must throw.
	// TODO: shortestSpan/longestSpan on an empty Span must throw.
	// TODO: same on a Span holding exactly one number.
	// TODO: 10,000+ numbers via addRange, timed. Then try 100,000.
	// TODO: copy construction and assignment -- prove the copy is independent.

	return (0);
}
