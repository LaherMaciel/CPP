/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:25:57 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/02/17 16:08:15 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/HumanB.hpp"
#include <iostream>

HumanB::HumanB(std::string humanBName)
{
	name = humanBName;
	weapon = NULL;
}

HumanB::~HumanB()
{
	
}

void	HumanB::setWeapon(Weapon& setWeapon)
{
	weapon = &setWeapon;
}

void	HumanB::attack()
{
	if (!weapon)
		std::cout << name << " doen't have a weapon " << std::endl;
	else
		std::cout << name << " attacks with their " << weapon->getType() << std::endl;
}