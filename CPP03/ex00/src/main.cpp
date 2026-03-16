/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 18:24:23 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/16 20:03:11 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClapTrap.hpp"
#include <iostream>

int main ()
{
	ClapTrap firstBorn("Matavelianopolizanatograpatitipanianaco Second Junior");
	ClapTrap secondBorn("AnotherOne");
	ClapTrap nextOne(firstBorn);
	ClapTrap djKhaled("Random person");

	std::cout << std::endl;
	firstBorn.attack("Poor random guy!");
	std::cout << std::endl;

	secondBorn.takeDamage(6);
	std::cout << std::endl;
	secondBorn.beRepaired(3);
	std::cout << std::endl;
	secondBorn.takeDamage(12);
	std::cout << std::endl;
	secondBorn.attack("Poor random guy!");
	std::cout << std::endl;
	secondBorn.beRepaired(4);
	std::cout << std::endl;
	secondBorn.attack("Poor random guy!");
	std::cout << std::endl;

	djKhaled = secondBorn;
	std::cout << std::endl;
	djKhaled.takeDamage(2);
	std::cout << std::endl;
	djKhaled.beRepaired(14);
	std::cout << std::endl;
	djKhaled.attack("Poor random guy!");
	std::cout << std::endl;
	return (0);
}
