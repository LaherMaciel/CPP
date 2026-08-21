/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 18:40:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/21 21:05:01 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <exception>
#include <iostream>

// Usage: ./btc input.txt      (the database is data.csv, alongside the binary)

int	main(int argc, char **argv)
{
	BitcoinExchange btc;

	if (argc != 2)
	{
		std::cout << "INVALID AMOUNT OF INPUT" << std::endl;
		return (0);
	}
	(void) argv;
	try
	{
		btc.loadDatabase("data.csv");
		btc.processInput(argv[1]);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
