/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:25:53 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/02/17 16:08:55 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/Weapon.hpp"

Weapon::Weapon(std::string setType)
{
	type = setType;
}


Weapon::~Weapon()
{
	
}


void	Weapon::setType(std::string setType)
{
	type = setType;
}

const std::string&	Weapon::getType(void) const
{
	return (type);
}