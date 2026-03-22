/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:20:08 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/20 15:12:47 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <string>

class Brain
{
	protected:
		std::string ideas[100];
	public:
		virtual ~Brain();
		Brain();
		Brain(const Brain& other);
		Brain&		operator=(const Brain& other);
		std::string	getIdea(int i) const;
		void		setIdea(std::string idea, int i);
};

#endif