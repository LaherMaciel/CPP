/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:29:06 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/20 15:12:16 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"
# include <string>

class Cat: public Animal
{
	private:
		Brain *brain;
	public:
		~Cat();
		Cat();
		Cat(const Cat& other);
		Cat& operator=(const Cat& other);
		void	makeSound() const;
		Brain&	getBrain();
};

#endif