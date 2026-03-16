/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:26:52 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/16 18:07:40 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::~Fixed()
{
}

Fixed::Fixed()
{
	_fixedPointValue = 0;
}

Fixed::Fixed(const Fixed& other)
{
	this->_fixedPointValue = other._fixedPointValue;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	this->_fixedPointValue = other._fixedPointValue;
	return (*this);
}

Fixed::Fixed(const int other)
{
	_fixedPointValue = other << _fractionalBits;
}

Fixed::Fixed(const float other)
{
	_fixedPointValue = roundf(other * (1 << _fractionalBits));
}

int Fixed::getRawBits() const
{
	return (_fixedPointValue);
}

void Fixed::setRawBits(int const raw)
{
	_fixedPointValue = raw;
}

float Fixed::toFloat( void ) const
{
	return (((float) _fixedPointValue) / (1 << _fractionalBits));
}

int Fixed::toInt( void ) const
{
	return (_fixedPointValue >> _fractionalBits);
}

std::ostream& operator<<(std::ostream& out, const Fixed& fixed)
{
	out << fixed.toFloat();
	return (out);
}

bool Fixed::operator==(const Fixed& fixed) const
{
	if (_fixedPointValue == fixed._fixedPointValue)
		return (true);
	return (false);
}

bool Fixed::operator!=(const Fixed& fixed) const
{
	if (_fixedPointValue != fixed._fixedPointValue)
		return (true);
	return (false);
}

bool Fixed::operator<=(const Fixed& fixed) const
{
	if (_fixedPointValue <= fixed._fixedPointValue)
		return (true);
	return (false);
}

bool Fixed::operator>=(const Fixed& fixed) const
{
	if (_fixedPointValue >= fixed._fixedPointValue)
		return (true);
	return (false);
}

bool Fixed::operator<(const Fixed& fixed) const
{
	if (_fixedPointValue < fixed._fixedPointValue)
		return (true);
	return (false);
}

bool Fixed::operator>(const Fixed& fixed) const
{
	if (_fixedPointValue > fixed._fixedPointValue)
		return (true);
	return (false);
}

Fixed Fixed::operator+(const Fixed& other)
{
	Fixed temp;
	temp.setRawBits(_fixedPointValue + other._fixedPointValue);
	return (temp);
}

Fixed Fixed::operator-(const Fixed& other)
{
	Fixed temp;
	temp.setRawBits(_fixedPointValue - other._fixedPointValue);
	return (temp);
}

Fixed Fixed::operator*(const Fixed& other)
{
	return (this->toFloat() * other.toFloat());
}

Fixed Fixed::operator/(const Fixed& other)
{
	return (this->toFloat() / other.toFloat());
}

Fixed Fixed::operator++()
{
	_fixedPointValue += 1;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed temp = *this;
	_fixedPointValue += 1;
	return (temp);
}

Fixed Fixed::operator--()
{
	_fixedPointValue -= 1;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed temp = *this;
	_fixedPointValue -= 1;
	return (temp);
}

Fixed Fixed::min(Fixed &a, Fixed &b)
{
	if (a._fixedPointValue < b._fixedPointValue)
		return (a);
	return (b);
}

Fixed Fixed::min(const Fixed &a, const Fixed &b)
{
	if (a._fixedPointValue < b._fixedPointValue)
		return (a);
	return (b);
}

Fixed Fixed::max(Fixed &a, Fixed &b)
{
	if (a._fixedPointValue > b._fixedPointValue)
		return (a);
	return (b);
}

Fixed Fixed::max(const Fixed &a, const Fixed &b)
{
	if (a._fixedPointValue > b._fixedPointValue)
		return (a);
	return (b);
}
