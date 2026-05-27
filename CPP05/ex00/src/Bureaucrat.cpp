/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:31:24 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/05/26 19:48:25 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ../include/Bureaucrat.hpp

Bureaucrat::~Bureaucrat()
{
	std::cout << "I hate Bureaucrats! " << name << "was " << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, int grade): _name(name), _grade(grade)
{
	if (_grade < 1)
		throw GradeTooHighException();
	if (_grade > 150)
		throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const &Bureaucrat other): _name(other._name) _grade(other._grade)
{
	std::cout << "Copy Constructor called" << std::endl;
}

//Just named it "that" just because I thought of (this != that) being funny
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& that)
{
	if (this != &that)
	{
		_name = that._name;
		_grade = that._grade;
	}
	std::cout << "Copy assignment operator called" << std::endl;
}

std::string Bureaucrat::getName() const
{
	return (_name);
}

int	Bureaucrat::getGrade(){
	return (_grade);
}

void Bureaucrat::incrementGrade()
{
	if (_grade - 1 < 1)
		throw GradeTooHighException();
	--_grade;
}

void Bureaucrat::decrementGrade()
{
	if (_grade + 1 > 150)
		throw GradeTooLowException();
	++_grade;
}

void operator<<(std::ostream& out, const Bureaucrat& bureaucrat)
{
	std::cout << bureaucrat._name << ", bureaucrat grade " << bureaucrat._grade << ".";
}
