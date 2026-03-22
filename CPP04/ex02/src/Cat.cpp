/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:28:47 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/22 19:52:44 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"
#include "../include/Brain.hpp"
#include <iostream>

Cat::~Cat()
{
	delete(brain);
	std::cout << "The Cat Destroyed!" << std::endl;
}
Cat::Cat(): Animal()
{
	type = "Cat";
	brain = new Brain();
	std::cout << "Cat Created using the Default Constructor!" << std::endl;
}

Cat::Cat(const Cat& other): Animal()
{
	type = other.type;
	brain = new Brain(*other.brain);
	std::cout << "The Cat was Created using Copy Constructor!"
		<< std::endl;
}

Cat&	Cat::operator=(const Cat& other)
{
	std::cout << "Copy Cat assignment operator called!" << std::endl;
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

void	Cat::makeSound() const
{
	std::cout << "YEAH MIAU! GIVE ME FOOD SLAVE!" << std::endl;
}

Brain&	Cat::getBrain()
{
	return (*brain);
}
