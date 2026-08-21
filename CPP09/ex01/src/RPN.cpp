/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 21:40:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/21 21:40:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

#include <stdexcept>
#include <sstream>
#include <string>

RPN::RPN(void) {}

RPN::RPN(RPN const& other) : _operands(other._operands) {}

RPN::~RPN(void) {}

RPN&	RPN::operator=(RPN const& other)
{
	if (this != &other)
		_operands = other._operands;
	return (*this);
}

// TODO: isOperator -- true for '+', '-', '*', '/'.

// TODO: applyOperator
//   Need TWO operands on the stack -- if _operands.size() < 2, throw.
//   POP ORDER MATTERS: the first pop is the RIGHT-hand operand,
//   the second pop is the LEFT-hand one.  "7 3 -" must be 7 - 3, not 3 - 7.
//   Guard division by zero.
//   Push the result back.

void	RPN::applyOperator(char op)
{
	(void) op;
}

// TODO: evaluate
//   Walk the expression token by token (std::istringstream >> std::string
//   splits on whitespace for free).
//   A token is either ONE digit (subject: operands are always < 10)
//   or ONE operator character.  Anything else -> throw.
//   Digit  -> push (c - '0').
//   Operator -> applyOperator.
//   At the end EXACTLY ONE value must remain, otherwise the expression
//   was malformed ("1 2" leaves two, "1 +" already threw).

int	RPN::evaluate(std::string const& expression)
{
	(void) expression;
	return (0);
}
