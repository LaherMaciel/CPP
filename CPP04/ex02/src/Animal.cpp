/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:13:41 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/22 19:53:02 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Animal.hpp"
#include <iostream>

Animal::~Animal()
{
	std::cout << "The Animal Destroyed!" << std::endl;
}
Animal::Animal()
{
	type = "";
	std::cout << "Animal Created using the Default Constructor!" << std::endl;
}

Animal::Animal(const Animal& other)
{
	type = other.type;
	std::cout << "The " << type << " Animal was Created using Copy Constructor!"
		<< std::endl;
}

Animal& Animal::operator=(const Animal& other)
{
	std::cout << "Copy Animal assignment operator called for " << type
		<< "!" << std::endl;
	std::cout << "And now " << type;
	type = other.type;
	std::cout << " is " << type << std::endl;
	return (*this);
}

std::string Animal::getType() const
{
	return (type);
}

void Animal::makeSound() const
{
	if (this->type == "")
		std::cout << "No Animal Sound!" << std::endl;
	else
		std::cout << type << " Sound!" << std::endl;
}
