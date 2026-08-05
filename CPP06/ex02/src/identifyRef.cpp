/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifyRef.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 21:30:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/03 21:36:16 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Functions.hpp"
#include <exception>
#include <iostream>

static int	checkC(Base& p)
{
	try
	{
		C& c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << "C" << std::endl;
		return (1);
	}
	catch (std::exception& e)
	{
		std::cout << "ERROR: NO VALID TYPE FOUND" << std::endl;
		return (0);
	}
}

static int	checkB(Base& p)
{
	try
	{
		B& b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << "B" << std::endl;
		return (1);
	}
	catch (std::exception& e)
	{
		return (checkC(p));
	}
}

static int	checkA(Base& p)
{
	try
	{
		A& a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "A" << std::endl;
		return (1);
	}
	catch (std::exception& e)
	{
		return (checkB(p));
	}
}

void	identify(Base& p)
{
	checkA(p);
}
