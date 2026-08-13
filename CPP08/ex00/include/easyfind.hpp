/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 00:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/13 00:00:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <exception>

// FUNCTION template this time, not a class template -- but the same rule as
// CPP07 applies: the definition must be visible where it is used, so it lives
// in the header.
//
// T is a CONTAINER of ints (std::vector<int>, std::list<int>, std::deque<int>).
// The subject does not ask you to support associative containers.

class NotFoundException : public std::exception
{
	public:
		virtual char const*	what(void) const throw();
};

template <typename T>
typename T::iterator	easyfind(T& container, int value);

// ============================ IMPLEMENTATION ============================
// TODO (you). Notes, not answers:
//
//  * The return type reads oddly on purpose. `typename` is REQUIRED there and
//    the compiler will tell you so if you drop it -- work out why before you
//    just paste it back in. It is the whole point of this exercise.
//  * <algorithm> is already included. One call does the searching; you are not
//    meant to write the loop by hand.
//  * "not found" has a well-defined representation in the STL. You do not need
//    a sentinel value or a bool flag -- the container already gives you one.
//  * Decide what happens on failure and be able to defend it. Throwing is the
//    obvious choice; the subject allows an error value too.

template <typename T>
typename T::iterator	easyfind(T& container, int value)
{
	(void)container;
	(void)value;
	return (container.end());
}

#endif
