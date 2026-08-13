/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 00:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/13 00:00:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>
#include <vector>

// CPP08 gives you no main -- writing the tests is part of the exercise.
// Start with vector, then prove the same call compiles unchanged for a
// std::list and a std::deque. That is what "works with any container" means.

int	main(void)
{
	std::vector<int>	v;

	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

	// TODO: find a value that IS there -- print it, and its distance from begin().
	// TODO: find a value that is NOT there -- catch whatever you decided to throw.
	// TODO: repeat both with std::list<int> and std::deque<int>, unchanged call.

	return (0);
}
