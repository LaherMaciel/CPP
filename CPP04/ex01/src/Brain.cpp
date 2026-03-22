/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:13:41 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/17 20:22:38 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Brain.hpp"
#include <iostream>

Brain::~Brain()
{
	std::cout << "The Brain Destroyed! Congrats, now you're Brainless!" << std::endl;
}
Brain::Brain()
{
	std::cout << "Brain Created using the Default Constructor!" << std::endl;
}

Brain::Brain(const Brain& other)
{
	for (int i = 0; i < 100; i++)
		ideas[i] = other.ideas[i];
	std::cout << "Brain Created, Ideas transferred to the new created Brain using Copy Constructor!"
		<< std::endl;
}

Brain& Brain::operator=(const Brain& other)
{
	std::cout << "Copy Ideas from one Brain to another using assignment operator!" << std::endl;
	for (int i = 0; i < 100; i++)
		ideas[i] = other.ideas[i];
	return (*this);
}

std::string	Brain::getIdea(int i) const
{
	return (ideas[i]);
}

void	Brain::setIdea(std::string idea, int i)
{
	ideas[i] = idea;
}