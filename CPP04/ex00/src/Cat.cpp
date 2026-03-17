/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:28:47 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/17 20:57:07 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"
#include <iostream>

Cat::~Cat()
{
	std::cout << "The Cat Destroid!" << std::endl;
}
Cat::Cat(): Animal()
{
	type = "Cat";
	std::cout << "Cat Created using the Default Constructor!" << std::endl;
}

Cat::Cat(const Cat& other): Animal()
{
	type = other.type;
	std::cout << "The Cat was Created using Copy Constructor!"
		<< std::endl;
}

Cat& Cat::operator=(const Cat& other)
{
	std::cout << "Copy Cat assignment operator called!" << std::endl;
		std::cout << "And now " << type;
	type = other.type;
	std::cout << " is " << type << std::endl;
	return (*this);
}

void Cat::makeSound() const
{
	std::cout << "YEAH MIAU! GIVE ME FOOD SLAVE!" << std::endl;
}
