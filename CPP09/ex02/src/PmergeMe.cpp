/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 19:05:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/22 19:05:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <stdexcept>
#include <string>

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

void	PmergeMe::parse(int argc, char **argv)
{
	(void) argc;
	(void) argv;
}

void	PmergeMe::sortVector(void) {}

void	PmergeMe::sortDeque(void) {}

void	PmergeMe::run(int argc, char **argv)
{
	parse(argc, argv);
}
