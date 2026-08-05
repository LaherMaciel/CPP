/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 00:20:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/06 00:26:07 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <exception>

// Class template. Same rule as ex00/ex01: the definitions must be visible where
// the class is used, so they live in this header (or in an Array.tpp included
// at the bottom of it -- the subject allows either).

template <typename T>
class Array
{
	public:
		Array(void);                        // empty array
		Array(unsigned int n);              // n elements, DEFAULT-initialised
		Array(Array const& other);          // must be a DEEP copy
		~Array(void);

		Array&			operator=(Array const& other);   // also a DEEP copy
		T&				operator[](unsigned int index);
		T const&		operator[](unsigned int index) const;
		unsigned int	size(void) const;

		class OutOfBoundsException : public std::exception
		{
			public:
				virtual char const*	what(void) const throw();
		};

	private:
		T*				_data;
		unsigned int	_size;
};

// ============================ IMPLEMENTATION ============================
// TODO (you): every body below is yours. Notes, not answers:
//
//  * MUST use new[]  ->  pairs with delete[]. Mixing new/delete[] is UB.
//  * "default-initialised": the subject's own hint is to compile
//        int* a = new int(); std::cout << *a;
//    and see what it prints. new T[n]() vs new T[n] is the whole question.
//  * DEEP copy: after `Array<int> b = a;` writing to b must NOT touch a.
//    Copying the pointer is the shallow bug -- and it also double-frees.
//  * operator= must survive self-assignment (a = a) and must not leak the
//    array it already owned.
//  * operator[] throws when index is out of range. Note the parameter is
//    UNSIGNED -- think about what the subject's `numbers[-2]` actually becomes.
//  * "preventive allocation forbidden": an empty Array allocates nothing.

template <typename T>
Array<T>::Array(void)
{
}

template <typename T>
Array<T>::Array(unsigned int n)
{
	(void)n;
}

template <typename T>
Array<T>::Array(Array const& other)
{
	(void)other;
}

template <typename T>
Array<T>::~Array(void)
{
}

template <typename T>
Array<T>&	Array<T>::operator=(Array const& other)
{
	(void)other;
	return (*this);
}

template <typename T>
T&	Array<T>::operator[](unsigned int index)
{
	(void)index;
	return (_data[0]);
}

template <typename T>
T const&	Array<T>::operator[](unsigned int index) const
{
	(void)index;
	return (_data[0]);
}

template <typename T>
unsigned int	Array<T>::size(void) const
{
	return (_size);
}

template <typename T>
char const*	Array<T>::OutOfBoundsException::what(void) const throw()
{
	return ("Array: index out of bounds");
}

#endif
