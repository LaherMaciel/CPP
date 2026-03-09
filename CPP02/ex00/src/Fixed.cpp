/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:26:52 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/09 16:28:59 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"
#include <iostream>

int Fixed::getRawBits() const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (_fixedPointValue);
}

void Fixed::setRawBits(int const raw)
{
	_fixedPointValue = raw;
}

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	_fixedPointValue = 0;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed& other)
{
	std::cout << "Copy constructor called" << std::endl;
	this->_fixedPointValue = other._fixedPointValue;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignation operator called" << std::endl;
	this->_fixedPointValue = other._fixedPointValue;
	return (*this);
}
