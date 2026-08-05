/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 14:15:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/05 21:11:53 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

// Templates MUST be defined in the header — the compiler needs the body
// at every point of use to generate a version per type.

template <typename T>
void	swap(T& a, T& b)
{
	T*	temp;

	temp = a;
	a = b;
	b = temp;
}

template <typename T>
T const &	min(T const& a, T const& b)
{
	if (a == b)
		return (b);
	if (a < b)
		return (a);
	return (b);
}

template <typename T>
T const &	max(T const& a, T const& b)
{
	if (a == b)
		return (b);
	if (a > b)
		return (a);
	return (b);
}

#endif
