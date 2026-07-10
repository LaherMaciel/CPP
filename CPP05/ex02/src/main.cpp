/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:24:09 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/07/10 15:43:54 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

static void	printTitle(const std::string &title, char fill)
{
	const int titleWidth = 36;
	int padding = (titleWidth - static_cast<int>(title.size())) / 2;
	int rightPad = titleWidth - static_cast<int>(title.size()) - padding;
	if (padding < 0) padding = 0;
	if (rightPad < 0) rightPad = 0;
	std::cout << std::string(padding, fill) << title << std::string(rightPad, fill) << std::endl;
}

void signingTests()
{
	try
	{
		Bureaucrat				trash("Trash", 150);
		Bureaucrat				lowest("Lowest", 140);
		Bureaucrat				low("Low", 50);
		Bureaucrat				ok("Ok", 20);
		ShrubberyCreationForm	shrubbery("shrubbery");
		RobotomyRequestForm		robotnik("Sonic");
		PresidentialPardonForm	jail("Jorge");

		std::cout << std::endl;
		printTitle("FORM SIGNING TESTS", '-');
		std::cout << std::endl;

		printTitle("Shrubbery (sign 145)", ' ');
		trash.signForm(shrubbery);
		lowest.signForm(shrubbery);
		std::cout << shrubbery << std::endl << std::endl;

		printTitle("Robotomy (sign 72)", ' ');
		lowest.signForm(robotnik);
		low.signForm(robotnik);
		std::cout << robotnik << std::endl << std::endl;

		printTitle("Presidential (sign 25)", ' ');
		low.signForm(jail);
		ok.signForm(jail);
		std::cout << jail << std::endl << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void	executionTests()
{
	try
	{
		Bureaucrat				lowest("Lowest", 140);
		Bureaucrat				low("Low", 50);
		Bureaucrat				ok("Ok", 20);
		Bureaucrat				best("Best", 2);
		ShrubberyCreationForm	shrubbery("shrubbery");
		RobotomyRequestForm		robotnik("Sonic");
		PresidentialPardonForm	jail("Jorge");

		std::cout << std::endl << std::endl;
		printTitle("FORM EXECUTION TESTS", '-');
		std::cout << std::endl;

		printTitle("Shrubbery (execution 137)", ' ');
		lowest.signForm(shrubbery);
		lowest.executeForm(shrubbery);
		low.executeForm(shrubbery);
		std::cout << std::endl;

		printTitle("Robotomy (execution 45)", ' ');
		low.signForm(robotnik);
		low.executeForm(robotnik);
		ok.executeForm(robotnik);
		std::cout << std::endl;

		printTitle("Presidential (execution 5)", ' ');
		ok.signForm(jail);
		ok.executeForm(jail);
		best.executeForm(jail);
		std::cout << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

int main()
{
	srand(time(NULL));
	signingTests();
	executionTests();
	return (0);
}
