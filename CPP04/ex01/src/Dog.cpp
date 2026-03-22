/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:28:51 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/22 19:52:51 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dog.hpp"
#include "../include/Brain.hpp"
#include <iostream>

Dog::~Dog()
{
	delete(brain);
	std::cout << "The Dog Destroyed!" << std::endl;
}

Dog::Dog() : Animal(), brain(new Brain())
{
	type = "Dog";
	std::cout << "Dog Created using the Default Constructor!" << std::endl;
}

Dog::Dog(const Dog& other): Animal(), brain(new Brain(*other.brain))
{
	type = other.type;
	std::cout << "The Dog was Created using Copy Constructor!"
		<< std::endl;
}

Dog&	Dog::operator=(const Dog& other)
{
	std::cout << "Copy Dog assignment operator called!" << std::endl;
	if (this != &other)
	{
		type = other.type;
		delete(brain);
		brain = new Brain(*other.brain);
	}
	return (*this);
}

void	Dog::makeSound() const
{
	std::cout << "HAU HAU FAM, THE DOGG IS IN THE HOUSE!" << std::endl;
}

Brain*	Dog::getBrain()
{
	return (brain);
}
