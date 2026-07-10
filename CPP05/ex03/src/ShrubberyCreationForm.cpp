/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:18:30 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/07/10 14:30:36 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
	: AForm(other), _target(other._target)
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	if (this != &other)
		AForm::operator=(other);
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void	ShrubberyCreationForm::execute(const Bureaucrat& executor) const
{
	checkExecution(executor);
	std::ofstream file((_target + "_shrubbery").c_str());
	if (!file.is_open())
		return ;
	file <<	"       ###\n"
			"      #o###\n"
			"    #####o###\n"
			"   #o#\\#|#/###\n"
			"   ###\\|/#o#\n"
			"    # }|{  #\n"
			"      }|{\n";
	file.close();
}
