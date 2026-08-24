/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeDeque.cpp                                  :+:      :+:    :+:   */
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
void	PmergeMe::runDeque(int argc, char **argv)
{
	double	start = nowMicroseconds();

	parse(_deque, argc, argv);
	double	elapsed = nowMicroseconds() - start;

	printContainer("Before:", _deque);

	start = nowMicroseconds();
	sortDeque();
	elapsed += nowMicroseconds() - start;

	printContainer("After:", _deque);
	printTime("deque", _deque.size(), elapsed);
}

void	PmergeMe::sortDeque(void) {}
