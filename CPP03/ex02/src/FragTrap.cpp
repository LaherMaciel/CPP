/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:38:13 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/17 18:57:46 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FragTrap.hpp"
#include <iostream>

FragTrap::~FragTrap()
{
	std::cout << name << " FragTrap Destroid!" << std::endl;
}

FragTrap::FragTrap()
{
	hitPoints = 100;
	maxHitPoints = 100;
	energyPoints = 100;
	attackDamage = 30;
	std::cout << name << " FragTrap Created!" << std::endl;
}

FragTrap::FragTrap(std::string setName) : ClapTrap(setName)
{
	hitPoints = 100;
	maxHitPoints = 100;
	energyPoints = 100;
	attackDamage = 30;
	std::cout << name << " FragTrap Created!" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
{
	std::cout << this->name << " FragTrap Created using Copy Constructor!"
		<< std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other)
{
	std::cout << "Copy FragTrap assignment operator called for " << name
		<< "!" << std::endl;
	ClapTrap::operator=(other);
	return (*this);
}

void FragTrap::highFivesGuys()
{
	if (energyPoints != 0 && hitPoints != 0)
		std::cout << this->name << " FragTrap Is requesting a High-Five!"
			<< std::endl;
	else
		std::cout << "Unable to Request High-Five:" << std::endl << "EnergyPoints = "
			<< energyPoints << std::endl << "HitPoints = " << hitPoints << std::endl;
}

