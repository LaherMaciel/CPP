/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVector.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 23:05:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/22 23:05:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <iostream>
#include <utility>
#include <algorithm>

// The clock covers parsing AND sorting -- "both the sorting part and the data
// management part" -- but NOT the printing. Writing 3000 numbers to a terminal
// costs far more than the sort and would drown the measurement.
void	PmergeMe::runVector(int argc, char **argv)
{
	double	start = nowMicroseconds();

	parse(_vector, argc, argv);
	double	elapsed = nowMicroseconds() - start;

	printContainer("Before:", _vector);

	start = nowMicroseconds();
	sortVector();
	elapsed += nowMicroseconds() - start;

	printContainer("After:", _vector);
	printTime("vector", _vector.size(), elapsed);
}

void	PmergeMe::sortVector(void)
{
	std::vector<std::pair<int, int> >	pairs;
	int									straggler = 0;
	bool								hasStraggler = false;

	makePairs(_vector, pairs, straggler, hasStraggler);

	// TEMPORARY -- proves the pairing before the recursion goes on top.
	for (std::size_t i = 0; i < pairs.size(); i++)
		std::cout << "  a=" << pairs[i].first << "  b=" << pairs[i].second << std::endl;
	if (hasStraggler)
		std::cout << "  straggler=" << straggler << std::endl;
}
