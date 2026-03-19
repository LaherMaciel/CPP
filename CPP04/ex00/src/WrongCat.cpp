/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:28:47 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/17 20:57:07 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongCat.hpp"
#include <iostream>

WrongCat::~WrongCat()
{
	std::cout << "The WrongCat Destroid!" << std::endl;
}
WrongCat::WrongCat(): WrongAnimal()
{
	type = "WrongCat";
	std::cout << "WrongCat Created using the Default Constructor!" << std::endl;
}

WrongCat::WrongCat(const WrongCat& other): WrongAnimal()
{
	type = other.type;
	std::cout << "The WrongCat was Created using Copy Constructor!"
		<< std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	std::cout << "Copy WrongCat assignment operator called!" << std::endl;
		std::cout << "And now " << type;
	type = other.type;
	std::cout << " is " << type << std::endl;
	return (*this);
}

void WrongCat::makeSound() const
{
	std::cout << "YEAH MIAU! GIVE ME FOOD SLAVE!" << std::endl;
}
