/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 15:40:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/20 17:27:22 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
	public:
		typedef typename std::stack<T>::container_type::iterator	iterator;

		MutantStack(void);
		MutantStack(MutantStack const& other);
		~MutantStack(void);
		MutantStack&	operator=(MutantStack const& other);

		iterator	begin(void);
		iterator	end(void);
};

# include "MutantStack.tpp"

#endif
