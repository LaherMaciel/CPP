/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 19:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/03 22:03:48 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Functions.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int	main(void)
{
	Base* p = NULL;

	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < 10; i++)
	{
		p = generate();
		identify(p);
		identify(*p);
		delete p;
		std::cout << std::endl;
	}
	return (0);
}
