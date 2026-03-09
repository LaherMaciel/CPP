/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:26:32 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/09 16:29:15 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP
# include <string>

class Fixed
{
	private:
		int					_fixedPointValue;
		static const int	_fractionalBits = 8;
	public:
		Fixed();
		~Fixed();
		Fixed(const Fixed& other);
		Fixed& operator=(const Fixed& other);
		int getRawBits() const;
		void setRawBits(int const raw);
};

#endif