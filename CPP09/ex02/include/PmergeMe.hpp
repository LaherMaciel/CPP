/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 19:05:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/22 21:43:56 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>
# include <iostream>
# include <utility>
# include <algorithm>
# include <cstddef>

// ex00 burned std::map, ex01 burned std::stack.
// The subject wants TWO containers and says to write the algorithm
// separately for each rather than one generic version.

// Validation is container-independent, so it lives in one plain function.
// Only the ALGORITHM has to be written twice -- the subject's "avoid a generic
// function" line is about the sort, not about data management.
int		parseToken(std::string const& token);
double	nowMicroseconds(void);
void	printTime(std::string const& name, std::size_t count, double us);

// The subject permits function templates in headers (p.70).
template <typename T>
void	printContainer(std::string const& label, T const& container);

class PmergeMe
{
	public:
		PmergeMe(void);
		PmergeMe(PmergeMe const& other);
		~PmergeMe(void);
		PmergeMe&	operator=(PmergeMe const& other);

		void	runVector(int argc, char **argv);
		void	runDeque(int argc, char **argv);

	private:
		std::vector<int>	_vector;
		std::deque<int>		_deque;

		void	sortVector(void);
		void	sortDeque(void);

		// Generic over the container, and PRIVATE. A member may already
		// name _vector and _deque, so nothing needs a getter.
		template <typename T>
		void	parse(T& container, int argc, char **argv);

		// T is the source container, P the container of pairs -- two different
		// types, so two template parameters. Works for vector and deque alike.
		template <typename T, typename P>
		void	makePairs(T const& src, P& pairs,
					int& straggler, bool& hasStraggler);
};


# include "PmergeMe.tpp"

#endif
