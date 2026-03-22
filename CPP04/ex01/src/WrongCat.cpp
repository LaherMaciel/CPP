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
#include "../include/Brain.hpp"
#include <iostream>

WrongCat::~WrongCat()
{
	delete(brain);
	std::cout << "The WrongCat Destroyed!" << std::endl;
}
WrongCat::WrongCat(): WrongAnimal()
{
	type = "WrongCat";
	brain = new Brain();
	std::cout << "WrongCat Created using the Default Constructor!" << std::endl;
}

WrongCat::WrongCat(const WrongCat& other): WrongAnimal()
{
	type = other.type;
	brain = other.brain;
	std::cout << "The WrongCat was Created using Copy Constructor!"
		<< std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	std::cout << "Copy WrongCat assignment operator called!" << std::endl;
	if (this != &other)
	{
		std::cout << "And now " << type;
		type = other.type;
		delete(brain);
		brain = new Brain(*other.brain);
		std::cout << " is " << type << std::endl;
	}
	return (*this);
}

void WrongCat::makeSound() const
{
	std::cout << "YEAH MIAU! GIVE ME FOOD SLAVE!" << std::endl;
}
