/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:28:51 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/22 19:53:40 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dog.hpp"
#include <iostream>

Dog::~Dog()
{
	std::cout << "The Dog Destroyed!" << std::endl;
}
Dog::Dog(): Animal()
{
	type = "Dog";
	std::cout << "Dog Created using the Default Constructor!" << std::endl;
}

Dog::Dog(const Dog& other): Animal()
{
	type = other.type;
	std::cout << "The Dog was Created using Copy Constructor!"
		<< std::endl;
}

Dog& Dog::operator=(const Dog& other)
{
	std::cout << "Copy Dog assignment operator called!" << std::endl;
		std::cout << "And now " << type;
	type = other.type;
	std::cout << " is " << type << std::endl;
	return (*this);
}

void Dog::makeSound() const
{
	std::cout << "HAU HAU FAM, THE DOGG IS IN THE HOUSE!" << std::endl;
}
