/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 00:20:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/19 20:24:56 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <exception>
# include <cstddef>

template <typename T>
class Array
{
	public:
		Array(void);
		Array(unsigned int n);
		Array(Array const& other);
		~Array(void);

		Array&			operator=(Array const& other);
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

template <typename T>
Array<T>::Array(void)
{
	_size = 0;
	_data = NULL;
}

template <typename T>
Array<T>::Array(unsigned int n)
{
	_size = n;
	if (_size == 0)
		_data = NULL;
	else
		_data = new T[_size]();
}

template <typename T>
Array<T>::Array(Array const& other)
{
	unsigned int i = 0;
	_size = other._size;
	if (_size == 0)
	{
		_data = NULL;
		return ;
	}
	_data = new T[_size]();

	try 
	{
		while (i < _size)
		{
			_data[i] = other._data[i];
			i++;
		}
	}
	catch (...)
	{
		delete [] _data;
		throw;
	}
}

template <typename T>
Array<T>::~Array(void)
{
	delete[] _data;
}

template <typename T>
Array<T>&	Array<T>::operator=(Array const& other)
{
	if (this == &other)
		return (*this);

	if (other._size == 0)
	{
		delete[] _data;
		_data = NULL;
		_size = 0;
		return (*this);
	}
	T* tmp = new T[other._size]();
	unsigned int i = 0;

	try
	{
		while (i < other._size)
		{
			tmp[i] = other._data[i];
			i++;
		}
	}
	catch (...)
	{
		delete[] tmp;
		throw;
	}
	delete[] _data;
	_size = other._size;
	_data = tmp;
	return (*this);
}

template <typename T>
T&	Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw OutOfBoundsException();
	return (_data[index]);
}

template <typename T>
T const&	Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw OutOfBoundsException();
	return (_data[index]);
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
