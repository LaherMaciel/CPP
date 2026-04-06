/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:14:01 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/24 14:42:53 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <string>

class Animal
{
	protected:
		std::string type;
	public:
		virtual ~Animal();
		Animal();
		Animal(const Animal& other);
		Animal& operator=(const Animal& other);
		std::string	getType() const;
		virtual void	makeSound() const = 0;
};

#endif