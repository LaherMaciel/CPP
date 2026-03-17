/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:02:35 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/17 18:29:07 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClapTrap.hpp"
#include <iostream>

ClapTrap::~ClapTrap()
{
	std::cout << name << " ClapTrap Destroid!" << std::endl;
	std::cout << std::endl;
}

ClapTrap::ClapTrap()
{
	name = "";
	hitPoints = 10;
	maxHitPoints = 10;
	energyPoints = 10;
	attackDamage = 0;
	std::cout << name << " ClapTrap Created!" << std::endl;
	std::cout << std::endl;
}

ClapTrap::ClapTrap(std::string setName)
{
	name = setName;
	hitPoints = 10;
	maxHitPoints = 10;
	energyPoints = 10;
	attackDamage = 0;
	std::cout << name << " ClapTrap Created!" << std::endl;
	std::cout << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other)
{
	this->name = other.name;
	this->hitPoints = other.hitPoints;
	this->maxHitPoints = other.maxHitPoints;
	this->energyPoints = other.energyPoints;
	this->attackDamage = other.attackDamage;
	std::cout << this->name << " ClapTrap Created using Copy Constructor!"
		<< std::endl;
	std::cout << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << "Copy assignment operator called for " << name
		<< "!" << std::endl;
	std::cout << "And now " << this->name;
	this->name = other.name;
	this->hitPoints = other.hitPoints;
	this->maxHitPoints = other.maxHitPoints;
	this->energyPoints = other.energyPoints;
	this->attackDamage = other.attackDamage;
	std::cout << " is " << name << std::endl;
	std::cout << std::endl;
	return (*this);
}

void	ClapTrap::attack(const std::string& target)
{
	if (energyPoints != 0 && hitPoints != 0)
	{
		std::cout << name << " ClapTrap attacked " << target << " causing "
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

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (hitPoints <= amount)
	{
		hitPoints = 0;
		std::cout << name << " ClapTrap received " << amount
			<< " of Damage and is Totally Damaged!" << std::endl;
	}
	else
	{
		hitPoints -= amount;
		std::cout << name << " ClapTrap Received " << amount << " Damaged!"
			<< std::endl;
	}
	std::cout << name << " Current hitPoint = " << hitPoints << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	switch (energyPoints)
	{
		case 0:
			std::cout << "Unable to repair, energyPoints = " << energyPoints
				<< std::endl;
			break ;
		default:
			if (hitPoints + amount > maxHitPoints)
			{
				hitPoints = maxHitPoints;
				std::cout << name << " ClapTrap Received " << amount
					<< " and is now Fully Repaired!" << std::endl;
			}
			else
			{
				hitPoints += amount;
				std::cout << name << " ClapTrap " << amount << " of Repair!"
					<< std::endl;
			}
			std::cout << name << " Current hitPoint = " << hitPoints << std::endl;
			energyPoints--;
			std::cout << "EnergyPoints = " << energyPoints << std::endl;
	}
}
