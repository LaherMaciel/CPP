/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 23:05:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/22 23:05:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_TPP
# define PMERGEME_TPP

# include "PmergeMe.hpp"

template <typename T>
void	printContainer(std::string const& label, T const& container)
{
	typename T::const_iterator	it;

	std::cout << label;
	for (it = container.begin(); it != container.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

template <typename T>
void	PmergeMe::parse(T& container, int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
		container.push_back(parseToken(argv[i]));
}

// One comparison per pair: .first is the larger (a), .second the smaller (b).
// An odd count leaves one element with no partner -- it is NOT a pair, so it
// never enters the pair container. No sentinel, nothing ambiguous.
template <typename T, typename P>
void	PmergeMe::makePairs(T const& src, P& pairs,
			int& straggler, bool& hasStraggler)
{
	std::size_t	i = 0;

	hasStraggler = (src.size() % 2 != 0);
	if (hasStraggler)
		straggler = src[src.size() - 1];
	while (i + 1 < src.size())
	{
		pairs.push_back(std::make_pair(
			std::max(src[i], src[i + 1]),
			std::min(src[i], src[i + 1])));
		i += 2;
	}
}

#endif
