/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 21:30:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/03 21:30:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Functions.hpp"
#include <cstdlib>
#include <iostream>

Base*	generate(void)
{
	int		rand_val;
	Base*	p = NULL;

	rand_val = rand() % 3;
	switch (rand_val)
	{
		case 0:
			p = new A;
			break ;
		case 1:
			p = new B;
			break ;
		case 2:
			p = new C;
			break ;
		default:
			std::cout << "generate error" << std::endl;
	}
	return (p);
}
