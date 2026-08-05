/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 22:35:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/05 23:50:51 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>
#include <string>

void	printConst(std::string const& str)
{
	std::cout << "const " << str << std::endl;
}

void	noConst(std::string& str)
{
	str = "submit";
}

void	printConstNbr(int const& nbr)
{
	std::cout << "const " << nbr << std::endl;
}

void	noConstNbr(int& nbr)
{
	nbr = 42;
}

int	main(void)
{
	std::string arr[7] = {"This", "is", "an", "array", "please",
			"work", "I'm to lazy"};
	size_t length = sizeof(arr) / sizeof(arr[0]);
	int myNumbers[5] = {10, 20, 30, 40, 50};
	size_t getArrayLength = sizeof(myNumbers) / sizeof(myNumbers[0]);

	::iter(arr, length, printConst);
	::iter(arr, length, noConst);
	for (size_t i = 0; i < length; i++)
	{
		std::cout << arr[i] << std::endl;
	}

	::iter(myNumbers, getArrayLength, printConstNbr);
	::iter(myNumbers, getArrayLength, noConstNbr);
	for (size_t i = 0; i < getArrayLength; i++)
	{
		std::cout << myNumbers[i] << std::endl;
	}
	return (0);
}
