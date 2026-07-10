/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:31:24 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/07/10 15:48:37 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"

Bureaucrat::Bureaucrat(const std::string& name, int grade): _name(name), _grade(grade)
{
	if (_grade < HIGHEST_GRADE)
		throw GradeTooHighException();
	if (_grade > LOWEST_GRADE)
		throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& other): _name(other._name), _grade(other._grade)
{
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& that)
{
	if (this != &that)
		_grade = that._grade;
	return (*this);
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "I hate Bureaucrats! " << _name << " was fired!" << std::endl;
}

const std::string& Bureaucrat::getName() const
{
	return (_name);
}

int	Bureaucrat::getGrade() const
{
	return (_grade);
}

void Bureaucrat::incrementGrade()
{
	if (_grade - 1 < HIGHEST_GRADE)
		throw GradeTooHighException();
	--_grade;
}

void Bureaucrat::decrementGrade()
{
	if (_grade + 1 > LOWEST_GRADE)
		throw GradeTooLowException();
	++_grade;
}

void	Bureaucrat::signForm(AForm& form)
{
	if (form.getIsSigned())
	{
		std::cout << _name << " couldn't sign " << form.getName()
			<< " because it is already signed." << std::endl;
		return ;
	}
	try
	{
		form.beSigned(*this);
		std::cout << _name << " signed " << form.getName() << "." << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << _name << " couldn't sign " << form.getName() <<
		" because " << e.what() << "." << std::endl;
	}
}

void	Bureaucrat::executeForm(const AForm& form) const
{
	try
	{
		form.execute(*this);
		std::cout << _name << " executed " << form.getName() << "."
			<< std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << _name << " couldn't execute " << form.getName()
			<< " because " << e.what() << "." << std::endl;
	}
}

std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat)
{
	out << bureaucrat.getName() << ", bureaucrat grade "
		<< bureaucrat.getGrade() << ".";
	return (out);
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Bureaucrat: grade too high (Highest is 1)");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Bureaucrat: grade too low (Lowest is 150)");
}
