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
	(void) argc;
	(void) argv;
	return (0);
}
