/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:58:20 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/07/13 15:48:51 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <string>
#include <iostream>

int	main(int argv, char **argc)
{
	if (argv != 2)
	{
		std::cout << "Error: Invalid amount of input!" << std::endl;
		return (0);
	}
	ScalarConverter::convert(argc[1]);
	return (0);
}