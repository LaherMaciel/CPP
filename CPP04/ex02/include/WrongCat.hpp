/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:49:43 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/20 10:48:22 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

# include "WrongAnimal.hpp"
#include "Brain.hpp"
# include <string>

class WrongCat: public WrongAnimal
{
	private:
		Brain *brain;
	public:
		~WrongCat();
		WrongCat();
		WrongCat(const WrongCat& other);
		WrongCat& operator=(const WrongCat& other);
		void	makeSound() const;
};

#endif