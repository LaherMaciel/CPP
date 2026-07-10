/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 19:24:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/06/25 09:25:02 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

# include <string>
# include <iostream>
# include <exception>
# include <ctime>

class Bureaucrat;

class AForm
{
	private:
		const std::string	_name;
		bool				_isSigned;
		const int			_gradeToSign;
		const int			_gradeToExecute;

	public:
		class FormNotSignedException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class GradeTooHighException: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		AForm(const std::string& name, const int gradeToSign,
			const int gradeToExecute);
		AForm(const AForm& other);
		AForm& operator=(const AForm& other);
		virtual ~AForm();
		const std::string&	getName() const;
		int					getGradeToExecute() const;
		int					getGradeToSign() const;
		bool				getIsSigned() const;
		void				beSigned(const Bureaucrat& bureaucrat);
		virtual void		execute(Bureaucrat const & executor) const = 0;

	protected:
		void				checkExecution(const Bureaucrat& executor) const;
};

std::ostream& operator<<(std::ostream& out, const AForm& aform);

# endif