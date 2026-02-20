/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 14:23:24 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/02/02 18:27:49 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"
#include <iostream>

Zombie* zombieHorde(int N, std::string name);

int main(int ac, char **av)
{
	Zombie	*horde;
	int		i;
	int		n;

	if (ac != 1)
	{
		n = ac;
		horde = zombieHorde(n, av[n - 1]);
	}
	else
	{
		n = 5;
		horde = zombieHorde(n, "MobZombie");
	}
	i = -1;
	while (++i < n)
		horde[i].announce();
	delete[] horde;
	return (0);
}
