/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 19:05:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/22 21:44:50 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <exception>
#include <iostream>

int	main(int argc, char **argv)
{
	PmergeMe	sorter;

	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	try
	{
		sorter.runVector(argc, argv);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	try
	{
		sorter.runDeque(argc, argv);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
 