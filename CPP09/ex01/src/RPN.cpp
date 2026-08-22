/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 21:40:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/22 18:42:02 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

#include <stdexcept>
#include <sstream>
#include <string>
#include <cctype>
#include <climits>

RPN::RPN(void) {}

RPN::RPN(RPN const& other) : _operands(other._operands) {}

RPN::~RPN(void) {}

RPN&	RPN::operator=(RPN const& other)
{
	if (this != &other)
		_operands = other._operands;
	return (*this);
}

bool	isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Every operation is checked BEFORE it runs -- signed overflow is undefined
// behaviour, so the result cannot be computed and inspected afterwards.
static int	safeAdd(int a, int b)
{
	if (b > 0 && a > INT_MAX - b)
		throw std::runtime_error("Error");
	if (b < 0 && a < INT_MIN - b)
		throw std::runtime_error("Error");
	return (a + b);
}

static int	safeSub(int a, int b)
{
	if (b < 0 && a > INT_MAX + b)
		throw std::runtime_error("Error");
	if (b > 0 && a < INT_MIN + b)
		throw std::runtime_error("Error");
	return (a - b);
}

static int	safeMul(int a, int b)
{
	if (a == 0 || b == 0)
		return (0);
	if (a > 0 && b > 0 && a > INT_MAX / b)
		throw std::runtime_error("Error");
	if (a > 0 && b < 0 && b < INT_MIN / a)
		throw std::runtime_error("Error");
	if (a < 0 && b > 0 && a < INT_MIN / b)
		throw std::runtime_error("Error");
	if (a < 0 && b < 0 && a < INT_MAX / b)
		throw std::runtime_error("Error");
	return (a * b);
}

// Only the DIVISOR can be zero -- 0 / 2 is a valid 0.
// INT_MIN / -1 is the second undefined division: the answer is +2147483648,
// which does not exist in int, and on x86 it traps in hardware.
static int	safeDiv(int a, int b)
{
	if (b == 0)
		throw std::runtime_error("Error");
	if (a == INT_MIN && b == -1)
		throw std::runtime_error("Error");
	return (a / b);
}

void	RPN::applyOperator(char op)
{
	int	right;
	int	left;

	if (_operands.size() < 2)
		throw std::runtime_error("Error");
	right = _operands.top();
	_operands.pop();
	left = _operands.top();
	_operands.pop();
	switch (op)
	{
		case '+':
			_operands.push(safeAdd(left, right));
			break ;
		case '-':
			_operands.push(safeSub(left, right));
			break ;
		case '*':
			_operands.push(safeMul(left, right));
			break ;
		case '/':
			_operands.push(safeDiv(left, right));
			break ;
	}
}

int	RPN::evaluate(std::string const& expression)
{
	std::istringstream	ss(expression);
	std::string			token;

	while (ss >> token)
	{
		if (token.size() != 1)
			throw std::runtime_error("Error");
		if (isOperator(token[0]))
		{
			applyOperator(token[0]);
			continue ;
		}
		if (!std::isdigit(static_cast<unsigned char>(token[0])))
			throw std::runtime_error("Error");
		_operands.push(token[0] - '0');
	}
	if (_operands.size() != 1)
		throw std::runtime_error("Error");
	return (_operands.top());
}
