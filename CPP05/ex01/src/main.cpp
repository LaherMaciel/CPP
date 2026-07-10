/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:24:09 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/07/10 15:10:26 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

static void	printTitle(const std::string &title, char fill)
{
	const int titleWidth = 36;
	int padding = (titleWidth - static_cast<int>(title.size())) / 2;
	int rightPad = titleWidth - static_cast<int>(title.size()) - padding;

	if (padding < 0)
		padding = 0;
	if (rightPad < 0)
		rightPad = 0;
	std::cout << std::string(padding, fill) << title << std::string(rightPad, fill) << std::endl;
}

void	gradeTests()
{
	printTitle("BUREAUCRAT GRADE TEST", '-');
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
	printTitle("FORM  GRADE TEST", '-');
	std::cout << std::endl;
	printTitle("Signing Grade", ' ');

	try
	{
		Form	formLowestGrade("TrashForm", 151, 50);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		Form	formBestLiar("2Good2BeTrue", 0, 50);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;
	printTitle("Executing Grade", ' ');

	try
	{
		Form	formLowestGrade("WorthlessForm", 75, 151);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		Form	formBestLiar("UltimateCorruptionForm", 75, 0);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;
}

void	printTests()
{
	std::cout << std::endl;
	printTitle("BUREAUCRAT PRINT TEST", '-');
	std::cout << std::endl;

	try
	{
		Bureaucrat	LazyMan("LazyMan", 150);
		std::cout << LazyMan.getName() << ", bureaucrat grade " << LazyMan.getGrade() << ";" << std::endl;
		std::cout << LazyMan << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;
	printTitle("FORM PRINT TEST", '-');
	std::cout << std::endl;

	try
	{
		Form	trashForm("TrashForm", 150, 75);
		std::cout << trashForm << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;
}

void gradeChangeTests()
{
	std::cout << std::endl;
	printTitle("BUREAUCRAT GRADE CHANGE TESTS", '-');
	std::cout << std::endl;

	try
	{
		Bureaucrat	LazyMan("LazyMan", 150);
		std::cout << LazyMan.getName() << ", bureaucrat grade " << LazyMan.getGrade() << ";" << std::endl;
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
		std::cout << burGoodLiar.getName() << ", bureaucrat grade " << burGoodLiar.getGrade() << ";" << std::endl;
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

	std::cout << std::endl;
}

void signingTests()
{
	try
	{
		Bureaucrat	lowBureaucrat("lowBureaucrat", 76);
		Bureaucrat	okBureaucrat("okBureaucrat", 75);
		Bureaucrat	ultraProMaxBureaucrat("UltraProMaxBureaucrat", 40);
		Form		flyForm("Fly Permit", 75, 50);
		Form		newCarsForm("Car Purchases Form", 50, 25);

		std::cout << std::endl;
		printTitle("FORM SIGNING TESTS", '-');
		std::cout << std::endl;
		printTitle("Bureaucrat Side Signing", ' ');
		std::cout << std::endl;
		std::cout << flyForm << std::endl << std::endl;

		lowBureaucrat.signForm(flyForm);
		std::cout << std::endl;
		std::cout << flyForm << std::endl << std::endl;
		okBureaucrat.signForm(flyForm);
		std::cout << std::endl;
		std::cout << flyForm << std::endl << std::endl;
		ultraProMaxBureaucrat.signForm(flyForm);
		std::cout << std::endl;
		std::cout << flyForm << std::endl << std::endl;

		printTitle("Form Side Signing", ' ');
		std::cout << std::endl;
		std::cout << newCarsForm << std::endl << std::endl;

		try
		{
			std::cout << std::endl;
			newCarsForm.beSigned(lowBureaucrat);
			std::cout << lowBureaucrat.getName() << " signed " << newCarsForm.getName() << "." << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << lowBureaucrat.getName() << " couldn't sign " << newCarsForm.getName() <<
			" because " << e.what() << "." << std::endl;
		}
		std::cout << std::endl;
		std::cout << newCarsForm << std::endl;

		try
		{
			std::cout << std::endl;
			newCarsForm.beSigned(okBureaucrat);
			std::cout << okBureaucrat.getName() << " signed " << newCarsForm.getName() << "." << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << okBureaucrat.getName() << " couldn't sign " << newCarsForm.getName() <<
			" because " << e.what() << "." << std::endl;
		}
		std::cout << std::endl;
		std::cout << newCarsForm << std::endl;
		try
		{
			std::cout << std::endl;
			newCarsForm.beSigned(ultraProMaxBureaucrat);
			std::cout << ultraProMaxBureaucrat.getName() << " signed " << newCarsForm.getName() << "." << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << ultraProMaxBureaucrat.getName() << " couldn't sign " << newCarsForm.getName() <<
			" because " << e.what() << "." << std::endl;
		}
		std::cout << std::endl;
		std::cout << newCarsForm << std::endl;
		std::cout << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

int main()
{
	gradeTests();
	printTests();
	gradeChangeTests();
	signingTests();
	return (0);
}
