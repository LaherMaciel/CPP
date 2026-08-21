/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 00:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/20 13:33:56 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <list>

void	vectorTest()
{
	std::vector<int>			v;
	std::vector<int>::iterator	it;

	for (int val = 10; val < 50; val += 10)
	{
		v.push_back(val);
		if (val == 30)
			v.push_back(20);
	}

	std::cout << std::endl << std::endl << "VECTOR TEST" << std::endl;
	for (int val = 10; val < 60; val += 10)
	{
		std::cout << "trying to find " << val << std::endl;
		try
		{
			it = easyfind(v, val);
			std::cout << "Returned value: " << *it << std::endl;
			std::cout << "Position: " << std::distance(v.begin(), it) << std::endl << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << "easyfind: value not found" << std::endl;
		}
	}
}

void	dequeTest()
{
	std::deque<int>				d;
	std::deque<int>::iterator	it;

	for (int val = 10; val < 50; val += 10)
	{
		d.push_back(val);
		if (val == 30)
			d.push_back(20);
	}

	std::cout << std::endl << std::endl << "DEQUE TEST" << std::endl;
	for (int val = 10; val < 60; val += 10)
	{
		std::cout << "trying to find " << val << std::endl;
		try
		{
			it = easyfind(d, val);
			std::cout << "Returned value: " << *it << std::endl;
			std::cout << "Position: " << std::distance(d.begin(), it) << std::endl << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << "easyfind: value not found" << std::endl;
		}
	}
}

void	listTest()
{
	std::list<int>				l;
	std::list<int>::iterator	it;

	for (int val = 10; val < 50; val += 10)
	{
		l.push_back(val);
		if (val == 30)
			l.push_back(20);
	}

	std::cout << std::endl << std::endl << "LIST TEST" << std::endl;
	for (int val = 10; val < 60; val += 10)
	{
		std::cout << "trying to find " << val << std::endl;
		try
		{
			it = easyfind(l, val);
			std::cout << "Returned value: " << *it << std::endl;
			std::cout << "Position: " << std::distance(l.begin(), it) << std::endl << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << "easyfind: value not found" << std::endl;
		}
	}
}

void	setTest()
{
	std::set<int>			s;
	std::set<int>::iterator	it;

	for (int val = 10; val < 50; val += 10)
	{
		s.insert(val);
		if (val == 30)
			s.insert(20);
	}

	std::cout << std::endl << std::endl << "SET TEST" << std::endl;
	for (int val = 10; val < 60; val += 10)
	{
		std::cout << "trying to find " << val << std::endl;
		try
		{
			it = easyfind(s, val);
			std::cout << "Returned value: " << *it << std::endl;
			std::cout << "Position: " << std::distance(s.begin(), it) << std::endl << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << "easyfind: value not found" << std::endl;
		}
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
