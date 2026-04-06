/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <lawences@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:14:05 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/04/06 13:41:12 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"
#include <iostream>

int main( void )
{
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	Fixed c(5);

	std::cout << "	a = " << a << std::endl;
	std::cout << "	++a = " << ++a << std::endl;
	std::cout << "	a = "  << a << std::endl;
	std::cout << "	a++ = " << a++ << std::endl;
	std::cout << "	a = " << a << std::endl;
	std::cout << "	b = " << b << std::endl;
	std::cout << "	c = " << c << std::endl;
	std::cout << "	c + a = " << c << " + " << a << " = "<< c + a << std::endl;
	std::cout << "	c - a = " << c << " - " << a << " = " << c - a << std::endl;
	std::cout << "	c * a = " << c << " * " << a << " = " << c * a << std::endl;
	std::cout << "	c / a = " << c << " / " << a << " = " << c / a << std::endl;
	std::cout << "	" << Fixed::max( a, b ) << std::endl;
	std::cout << "	" << Fixed::min( a, b ) << std::endl;

	return (0);
}
