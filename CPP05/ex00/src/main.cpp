/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:24:09 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/06/25 11:59:51 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
	try
	{
		Bureaucrat	burLowestGrade("LaziestMan", 151);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		Bureaucrat	burBestLiar("TheBestLiar", -1);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;

	try
	{
		Bureaucrat	LazyMan("LazyMan", 150);
		std::cout << LazyMan.getName() << ", bureaucrat grade " <<
			LazyMan.getGrade() << ";" << std::endl;
		std::cout << LazyMan << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;

	try
	{
		Bureaucrat	LazyMan("LazyMan", 150);
		std::cout << LazyMan.getName() << ", Bureaucrat grade " <<
			LazyMan.getGrade() << ";" << std::endl;
		LazyMan.incrementGrade();
		std::cout << LazyMan << std::endl;
		LazyMan.incrementGrade();
		std::cout << LazyMan << std::endl;
		LazyMan.decrementGrade();
		std::cout << LazyMan << std::endl;
		LazyMan.decrementGrade();
		std::cout << LazyMan << std::endl;
		LazyMan.decrementGrade();
		std::cout << LazyMan << std::endl;
		LazyMan.decrementGrade();
		std::cout << LazyMan << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;

	try
	{
		Bureaucrat	burGoodLiar("TheGoodLiar", 1);
		std::cout << burGoodLiar.getName() << ", Bureaucrat grade " <<
			burGoodLiar.getGrade() << ";" << std::endl;
		burGoodLiar.decrementGrade();
		std::cout << burGoodLiar << std::endl;
		burGoodLiar.decrementGrade();
		std::cout << burGoodLiar << std::endl;
		burGoodLiar.incrementGrade();
		std::cout << burGoodLiar << std::endl;
		burGoodLiar.incrementGrade();
		std::cout << burGoodLiar << std::endl;
		burGoodLiar.incrementGrade();
		std::cout << burGoodLiar << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
