/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 19:24:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/06/25 11:16:15 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(const std::string& name, const int gradeToSign, const int gradeToExecute):
	_name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (_gradeToSign < HIGHEST_GRADE)
		throw GradeTooHighException();
	if (_gradeToSign > LOWEST_GRADE)
		throw GradeTooLowException();
	if (_gradeToExecute < HIGHEST_GRADE)
		throw GradeTooHighException();
	if (_gradeToExecute > LOWEST_GRADE)
		throw GradeTooLowException();
}

Form::Form(const Form& other): _name(other._name), _isSigned(other._isSigned),
	_gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
}

Form& Form::operator=(const Form& that)
{
	if (this != &that)
		_isSigned = that._isSigned;
	return (*this);
}

Form::~Form()
{
	std::cout << "I hate Forms! " << _name << " Destroyed!" << std::endl;
}

const std::string& Form::getName() const
{
	return (_name);
}

int	Form::getGradeToExecute() const
{
	return (_gradeToExecute);
}

int	Form::getGradeToSign() const
{
	return (_gradeToSign);
}

bool	Form::getIsSigned() const
{
	return (_isSigned);
}

void	Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	if (_isSigned)
		return ;
	_isSigned = true;
}

std::ostream& operator<<(std::ostream& out, const Form& form)
{
	out << "Form Name: " << form.getName() << ";" << std::endl <<
		"Grade to Sign: " << form.getGradeToSign() << ";" << std::endl <<
		"Signed Status: " << (form.getIsSigned() ?
			"Form Signed" : "Form not Signed") << ";" << std::endl <<
		"Grade to Execute: " << form.getGradeToExecute() << ";" << std::endl;
	return (out);
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Form: grade too high (Highest is 1)");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Form: grade too low (Lowest is 150)");
}
