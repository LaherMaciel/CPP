/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:31:20 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/05/26 19:41:18 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <string>
# include <exception>
# include <stdexcept>

class Bureaucrat:
{
	private:
		const std::string	_name;
		int					_grade;
	
	public:
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
	
	Bureaucrat(std::string name, int grade);
	Bureaucrat(const &Bureaucrat other);
	Bureaucrat& operator=(const Bureaucrat& other);
	~Bureaucrat();
	std::string getName() const;
	int			getGrade();
	void		increaseGrade();
	void		decreaseGrade();
}

void operator<<(std::ostream& out, const Bureaucrat& bureaucrat)

#endif