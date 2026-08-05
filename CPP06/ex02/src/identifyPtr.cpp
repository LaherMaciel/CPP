/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifyPtr.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 21:30:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/03 21:36:27 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Functions.hpp"
#include <iostream>

static int	checkC(Base* p)
{
	C* c = dynamic_cast<C*>(p);
	if (c != NULL)
	{
		std::cout << "C" << std::endl;
		return (1);
	}
	return (0);
}

static int	checkB(Base* p)
{
	B* b = dynamic_cast<B*>(p);
	if (b != NULL)
	{
		std::cout << "B" << std::endl;
		return (1);
	}
	else
		return (checkC(p));
}

static int	checkA(Base* p)
{
	A* a = dynamic_cast<A*>(p);
	if (a != NULL)
	{
		std::cout << "A" << std::endl;
		return (1);
	}
	else
		return (checkB(p));
}

void	identify(Base* p)
{
	if (checkA(p) == 0)
		std::cout << "ERROR: NO VALID TYPE FOUND" << std::endl;
}
