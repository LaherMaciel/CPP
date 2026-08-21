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
# include <string>

// Container choice: std::stack.
// CPP09 rule -- ex00 used std::map, so map is forbidden here,
// and std::stack is forbidden in ex02.

class RPN
{
	public:
		RPN(void);
		RPN(RPN const& other);
		~RPN(void);
		RPN&	operator=(RPN const& other);

		int		evaluate(std::string const& expression);

	private:
		std::stack<int>	_operands;

		void	applyOperator(char op);
};

bool	isOperator(char c);

#endif
