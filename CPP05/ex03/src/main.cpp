/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 16:26:33 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/07/10 16:59:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Intern.hpp"

int main()
{
	Intern	someRandomIntern;
	AForm*	form;

	form = someRandomIntern.makeForm("RobotomyRequestForm", "Bender");
	if (form)
	{
		Bureaucrat  boss("Boss", 1);
		boss.signForm(*form);
		boss.executeForm(*form);
		delete form;
	}

	form = someRandomIntern.makeForm("CoffeeForm", "nobody");
	if (form)
		delete form;
	return (0);
}