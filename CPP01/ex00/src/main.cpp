/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 14:23:24 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/02/01 16:29:38 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"
#include <iostream>

void	randomChump(std::string randomChump);
Zombie	*newZombie(std::string name);

int main()
{
	Zombie	*z = newZombie("Foo");

	z->announce();
	randomChump("Zombie 2");
	delete z;
	return (0);
}