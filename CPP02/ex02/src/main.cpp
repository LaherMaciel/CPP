/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:14:05 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/09 20:09:31 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"
#include <iostream>

int main( void )
{
	/* Fixed a;
	Fixed const b( 10 ); */
	Fixed z(1);
	/* Fixed const c( 42.42f );
	Fixed const d( b );

	a = Fixed( 1234.4321f ); */

	Fixed e = z++;
	std::cout << "e = " << e << " z = " << z << std::endl;
	Fixed f = ++z;
	std::cout << "f = " << f << " z = " << z << std::endl;
	Fixed g = z--;
	std::cout << "g = " << g << " z = " << z << std::endl;
	Fixed h = --z;
	std::cout << "h = " << h << " z = " << z << std::endl;
/* 
	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;

	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;
 */
	return (0);
}