/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 00:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/19 11:46:41 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <list>

// CPP08 gives you no main -- writing the tests is part of the exercise.
// Start with vector, then prove the same call compiles unchanged for a
// std::list and a std::deque. That is what "works with any container" means.

void	vectorTest()
{
	std::vector<int>	v;

	for (int val = 10; val < 40; val += 10)
	{
		v.push_back(val);
	}
	v.push_back(20);
	v.push_back(40);

	std::cout << std::endl << std::endl << "VECTOR TEST" << std::endl;
	try
	{
		std::vector<int>::iterator it;
	
		for (int val = 10; val < 60; val += 10)
		{
			std::cout << "trying to find " << val << std::endl;
			it = easyfind(v, val);
			std::cout << "Returned value: " << *it << std::endl;
			std::cout << "Position: " << std::distance(v.begin(), it) << std::endl << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << "easyfind: value not found" << std::endl;
	}
}

void	dequeTest()
{
	std::deque<int> d;

	for (int val = 10; val < 40; val += 10)
	{
		d.push_back(val);
	}
	d.push_back(20);
	d.push_back(40);

	std::cout << std::endl << std::endl << "DEQUE TEST" << std::endl;
	try
	{
		std::deque<int>::iterator it;

		for (int val = 10; val < 60; val += 10)
		{
			std::cout << "trying to find " << val << std::endl;
			it = easyfind(d, val);
			std::cout << "Returned value: " << *it << std::endl;
			std::cout << "Position: " << std::distance(d.begin(), it) << std::endl << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << "easyfind: value not found" << std::endl;
	}
}

void	listTest()
{
	std::list<int> l;

	for (int val = 10; val < 40; val += 10)
	{
		l.push_back(val);
	}
	l.push_back(20);
	l.push_back(40);

	std::cout << std::endl << std::endl << "LIST TEST" << std::endl;
	try
	{
		std::list<int>::iterator it;

		for (int val = 10; val < 60; val += 10)
		{
			std::cout << "trying to find " << val << std::endl;
			it = easyfind(l, val);
			std::cout << "Returned value: " << *it << std::endl;
			std::cout << "Position: " << std::distance(l.begin(), it) << std::endl << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << "easyfind: value not found" << std::endl;
	}
}

void	setTest()
{
	std::set<int> s;

	for (int val = 10; val < 40; val += 10)
	{
		s.insert(val);
	}
	s.insert(20);
	s.insert(40);

	std::cout << std::endl << std::endl << "SET TEST" << std::endl;
	try
	{
		std::set<int>::iterator it;

		for (int val = 10; val < 60; val += 10)
		{
			std::cout << "trying to find " << val << std::endl;
			it = easyfind(s, val);
			std::cout << "Returned value: " << *it << std::endl;
			std::cout << "Position: " << std::distance(s.begin(), it) << std::endl << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << "easyfind: value not found" << std::endl;
	}
}

int	main(void)
{
	
	std::cout << std::endl << "EASYFIND TEST" << std::endl;
	vectorTest();
	dequeTest();
	listTest();
	setTest();

	return (0);
}
