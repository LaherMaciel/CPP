/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:13:41 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/17 20:22:38 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongAnimal.hpp"
#include <iostream>

WrongAnimal::~WrongAnimal()
{
	std::cout << "The " << type << " WrongAnimal Destroid!" << std::endl;
}
WrongAnimal::WrongAnimal()
{
	type = "";
	std::cout << "WrongAnimal Created using the Default Constructor!" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other)
{
	type = other.type;
	std::cout << "The " << type << " WrongAnimal was Created using Copy Constructor!"
		<< std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
	std::cout << "Copy WrongAnimal assignment operator called for " << type
		<< "!" << std::endl;
		std::cout << "And now " << type;
	type = other.type;
	std::cout << " is " << type << std::endl;
	return (*this);
}

std::string WrongAnimal::getType() const
{
	return (type);
}

void WrongAnimal::makeSound() const
{
	std::cout << "No Animal Sound!" << std::endl;
}
