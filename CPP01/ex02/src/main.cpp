/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 14:23:24 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/02/02 19:11:35 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main()
{
	std::string	message = "HI THIS IS BRAIN";
	std::string	&stringREF = message;
	std::string	*stringPTR = &message;

	std::cout << &message << std::endl;
	std::cout << &stringREF << std::endl; //references share the memory
		// address then the original variable address
	std::cout << stringPTR << std::endl  << std::endl;

	std::cout << message << std::endl;
	std::cout << stringREF << std::endl;
	std::cout << *stringPTR << std::endl; //Because the value that the
		// pointer stores is the address of the pointed variable
	return 0;
}
