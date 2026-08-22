/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 21:40:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/21 21:40:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

#include <exception>
#include <iostream>

// Usage: ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"   ->  42
// Subject: errors go to STANDARD ERROR (unlike ex00, which printed to stdout).

// TODO: main
//   argc must be exactly 2, otherwise error on std::cerr.
//   One try/catch around evaluate(); print the result on std::cout,
//   print "Error" on std::cerr for any failure.

int	main(int argc, char **argv)
{
	RPN	rpn;

	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	try
	{
		std::cout << rpn.evaluate(argv[1]) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
