/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 19:05:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/22 19:05:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>

// ex00 burned std::map, ex01 burned std::stack.
// The subject wants TWO containers and says to write the algorithm
// separately for each rather than one generic version.

class PmergeMe
{
	public:
		PmergeMe(void);
		PmergeMe(PmergeMe const& other);
		~PmergeMe(void);
		PmergeMe&	operator=(PmergeMe const& other);

		void	run(int argc, char **argv);

	private:
		std::vector<int>	_vector;
		std::deque<int>		_deque;

		void	parse(int argc, char **argv);
		void	sortVector(void);
		void	sortDeque(void);
};

#endif
