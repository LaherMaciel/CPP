/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:30:55 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/04/06 15:54:51 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScavTrap.hpp"
#include <iostream>

ScavTrap::~ScavTrap()
{
	std::cout << name << " ScavTrap Destroid!" << std::endl;
}

ScavTrap::ScavTrap()
{
	hitPoints = 100;
	maxHitPoints = 100;
	energyPoints = 50;
	attackDamage = 20;
	std::cout << name << " ScavTrap Created!" << std::endl;
}

ScavTrap::ScavTrap(std::string setName) : ClapTrap(setName)
{
	hitPoints = 100;
	maxHitPoints = 100;
	energyPoints = 50;
	attackDamage = 20;
	std::cout << name << " ScavTrap Created!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
{
	std::cout << this->name << " ScavTrap Created using Copy Constructor!"
		<< std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
	std::cout << "Copy ScavTrap assignment operator called for " << name
		<< "!" << std::endl;
	ClapTrap::operator=(other);
	return (*this);
}

void ScavTrap::guardGate()
{
	if (energyPoints != 0 && hitPoints != 0)
		std::cout << this->name << " ScavTrap Is Now in Gate Keeper Mode!"
			<< std::endl;
	else
		std::cout << "Unable to Activate Guard Mode:" << std::endl << "EnergyPoints = "
			<< energyPoints << std::endl << "HitPoints = " << hitPoints << std::endl;
}

void	ScavTrap::attack(const std::string& target)
{
	if (energyPoints != 0 && hitPoints != 0)
	{
		std::cout << name << " ScavTrap attacked " << target << " causing "
			<< attackDamage << " of damaged!" << std::endl;
		energyPoints--;
		std::cout << "EnergyPoints = " << energyPoints << std::endl;
	}
	else
	{
		std::cout << "Unable to Attack:" << std::endl << "EnergyPoints = "
		<< energyPoints << std::endl << "HitPoints = " << hitPoints << std::endl;
	}
}
