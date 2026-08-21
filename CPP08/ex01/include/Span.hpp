/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/20 16:43:10 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <exception>
# include <cstddef>
# include <iterator>

class Span
{
	public:
		Span(void);
		explicit Span(unsigned int n);
		Span(Span const& other);
		~Span(void);

		Span&	operator=(Span const& other);

		void			addNumber(int number);
		unsigned int	shortestSpan(void) const;
		unsigned int	longestSpan(void) const;

		template <typename ForwardIterator>
		void	addRange(ForwardIterator first, ForwardIterator last);

		class OutOfBoundsException : public std::exception
		{
			public:
				virtual char const*	what(void) const throw();
		};

	private:
		std::vector<int>	_numbers;
		unsigned int		_maxSize;
};

template <typename ForwardIterator>
void	Span::addRange(ForwardIterator first, ForwardIterator last)
{
	if (_numbers.size() + static_cast<std::size_t>(std::distance(first, last)) > _maxSize)
		throw OutOfBoundsException();
	_numbers.insert(_numbers.end(), first, last);
}

#endif
