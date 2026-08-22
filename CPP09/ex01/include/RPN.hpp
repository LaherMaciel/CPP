/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 21:40:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/21 21:40:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <list>
# include <string>

// Container: std::stack adapted over std::list.
// std::stack defaults to std::deque underneath; pinning std::list keeps
// deque free for ex02, which needs vector + deque.

class RPN
{
	public:
		RPN(void);
		RPN(RPN const& other);
		~RPN(void);
		RPN&	operator=(RPN const& other);

		int		evaluate(std::string const& expression);

	private:
		std::stack<int, std::list<int> >	_operands;

		void	applyOperator(char op);
};

bool	isOperator(char c);

#endif
