/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 15:37:32 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/02/01 15:44:33 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

/**
	This function creates a zombie, names it, and returns it so you can use it outside
	of the function scope.
 */
Zombie *newZombie(std::string name)
{
	return (new Zombie(name));
}
