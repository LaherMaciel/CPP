/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 19:24:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/06/24 15:31:05 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string& name, const int gradeToSign, const int gradeToExecute):
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

AForm::AForm(const AForm& other): _name(other._name), _isSigned(other._isSigned),
	_gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
}

AForm& AForm::operator=(const AForm& that)
{
	if (this != &that)
		_isSigned = that._isSigned;
	return (*this);
}

AForm::~AForm()
{
	std::cout << "I hate AForms! " << _name << " Destroyed!" << std::endl;
}

const std::string&	AForm::getName() const
{
	return (_name);
}

int	AForm::getGradeToExecute() const
{
	return (_gradeToExecute);
}

int	AForm::getGradeToSign() const
{
	return (_gradeToSign);
}

bool	AForm::getIsSigned() const
{
	return (_isSigned);
}

void	AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	if (_isSigned)
		return ;
	_isSigned = true;
}

void AForm::checkExecution(const Bureaucrat& executor) const
{
	if (!_isSigned)
		throw FormNotSignedException();
	if (executor.getGrade() > _gradeToExecute)
		throw GradeTooLowException();
}

std::ostream& operator<<(std::ostream& out, const AForm& Aform)
{
	out << "AForm Name: " << Aform.getName() << ";" << std::endl <<
		"Grade to Sign: " << Aform.getGradeToSign() << ";" << std::endl <<
		"Signed Status: " << (Aform.getIsSigned() ?
		"AForm Signed" : "AForm not Signed") << ";" << std::endl <<
		"Grade to Execute: " << Aform.getGradeToExecute() << ";" << std::endl;
	return (out);
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return ("AForm: grade too high (Highest is 1)");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("AForm: grade too low (Lowest is 150)");
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return ("AForm: form not signed");
}
