/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/18 21:00:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <stdexcept>

// NOT a template class -- N is a runtime unsigned int, not a template
// parameter. So the p.5 rule bites in full: NOTHING may be implemented in
// this header. Every body goes in Span.cpp.
//
// Orthodox Canonical Form is required (Module 02-09 rule): copy constructor,
// copy assignment operator, destructor. Add a default constructor too if you
// want one -- decide what N should be for a Span nobody sized, and be ready
// to defend it.

class Span
{
	public:
		Span(void);
		Span(unsigned int n);
		Span(Span const& other);
		~Span(void);

		Span&	operator=(Span const& other);

		void	addNumber(int number);
		int		shortestSpan(void) const;
		int		longestSpan(void) const;

		// The "it would be wonderful" bonus: fill from a range in ONE call.
		// This one MUST be a template (it takes any iterator type), which
		// means it is the ONE thing allowed to have its body in the header.
		// Declare it here; body goes at the bottom of this file.
		template <typename InputIterator>
		void	addRange(InputIterator first, InputIterator last);

	private:
		std::vector<int>	_numbers;
		unsigned int		_maxSize;
};

// ============================ NOTES, NOT ANSWERS ============================
//
//  * addNumber: throws when the Span is already full. Which exception? You
//    already picked a policy in ex00 -- stay consistent.
//  * shortestSpan / longestSpan: throw when 0 or 1 elements are stored,
//    because a span needs two numbers to exist.
//  * longestSpan is the easy one: it is (largest - smallest). <algorithm>
//    has two functions that hand you those directly. Do not write the loop.
//  * shortestSpan is the interesting one. The naive answer compares every
//    pair -- that is O(n^2), which is 100 MILLION comparisons at n = 10,000
//    and dies outright at n = 100,000. There is an O(n log n) route: the
//    closest two numbers must end up ADJACENT once the data is sorted.
//    Sort a COPY (do not mutate _numbers -- these are const member functions
//    for a reason), then walk it once.
//  * Watch the subtraction. shortestSpan on a Span holding INT_MIN and
//    INT_MAX overflows a signed int. Think about whether you care, and be
//    able to say what you decided.
//  * addRange must respect _maxSize too. Decide: reject the whole range up
//    front, or add until full and then throw? One of those leaves the Span
//    half-modified. Defend your choice.
//
// ======================== TEMPLATE IMPLEMENTATION ===========================
// (the only code allowed in this header -- it is a function template)

template <typename InputIterator>
void	Span::addRange(InputIterator first, InputIterator last)
{
	(void)first;
	(void)last;
}

#endif
