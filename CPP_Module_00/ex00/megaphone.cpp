/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:03:17 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/17 14:44:35 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int argc, char **argv)
{
	std::string  message;

	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		for (int a = 1; a < argc; ++a)
		{
			message = argv[a];
			for (int i = 0; message[i]; ++i)
			{
				if (std::islower(static_cast<unsigned char>(message[i])))
					message[i] = toupper(message[i]);
			}
			std::cout << message;
		}
		std::cout << std::endl;
	}
	return 0;
}
