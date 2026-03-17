/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 18:24:23 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/17 18:51:27 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FragTrap.hpp"
#include <iostream>

int main ()
{
	FragTrap firstBorn("Matavelianopolizanatograpatitipanianaco Second Junior");
	FragTrap secondBorn("AnotherOne");
	FragTrap nextOne(firstBorn);
	FragTrap djKhaled("Random person");

	std::cout << std::endl;
	firstBorn.attack("Poor random guy!");
	std::cout << std::endl;

	secondBorn.highFivesGuys();
	std::cout << std::endl;
	secondBorn.takeDamage(36);
	std::cout << std::endl;
	secondBorn.beRepaired(23);
	std::cout << std::endl;
	secondBorn.takeDamage(87);
	std::cout << std::endl;
	secondBorn.attack("Poor random guy!");
	std::cout << std::endl;
	secondBorn.beRepaired(44);
	std::cout << std::endl;
	secondBorn.attack("Poor random guy!");
	std::cout << std::endl;

	djKhaled = secondBorn;
	std::cout << std::endl;

	djKhaled.takeDamage(2);
	std::cout << std::endl;
	djKhaled.beRepaired(94);
	std::cout << std::endl;
	djKhaled.attack("Poor random guy!");
	std::cout << std::endl;
	return (0);
}
