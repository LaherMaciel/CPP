/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 16:04:17 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/07/10 16:26:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

Intern::Intern() {}
Intern::Intern(const Intern&) {}
Intern& Intern::operator=(const Intern&) { return (*this); }
Intern::~Intern() {}

static AForm* makeShrubbery(const std::string& target)
{
	return (new ShrubberyCreationForm(target));
}
static AForm* makeRobotomy(const std::string& target)
{
	return (new RobotomyRequestForm(target));
}
static AForm* makePresidential(const std::string& target)
{
	return (new PresidentialPardonForm(target));
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target)
{
	std::string names[3]
		= {"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};
	AForm* (*makers[3])(const std::string&)
		= {makeShrubbery, makeRobotomy, makePresidential};
	for (int i = 0; i < 3; i++)
	{
		if (names[i] == formName)
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (makers[i](target));
		}
	}
	std::cout << "Intern couldn't create " << formName
		<< ": form not found" << std::endl;
	return (NULL);
}

const char* Intern::FormNotFoundException::what() const throw()
{
	return ("Intern: form name not found");
}