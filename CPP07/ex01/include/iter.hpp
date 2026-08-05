/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 22:35:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/05 23:21:44 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

# include <cstddef>

template <typename T, typename F>
void	iter(T* array, size_t const length, F function)
{
	for (size_t i = 0; i < length; i++)
	{
		function(array[i]);
	}
}

#endif
