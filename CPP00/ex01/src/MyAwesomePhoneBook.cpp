/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyAwesomePhoneBook.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:03:17 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/01/30 19:30:33 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PhoneBook.hpp"
#include <iostream>
#include <string>

std::string trim_string(std::string str)
{
	size_t start;
	size_t end;

	start = str.find_first_not_of(" \t");
	if (start == std::string::npos)
		return "";
	end = str.find_last_not_of(" \t");
	return str.substr(start, end - start + 1);
}

int main()
{
	PhoneBook	phonebook;
	std::string command;

	std::cout << "Welcome to My Awesome Phone Book!" << std::endl;
	while (true)
	{
		std::cout << "Enter command (ADD, SEARCH, EXIT): ";
		std::getline(std::cin, command);
		//command = trim_string(command);
		if (command == "ADD")
			phonebook.add_contact();
		else if (command == "SEARCH")
			phonebook.search_contacts();
		else if (command == "EXIT")
			break;
		else
			std::cout << "Invalid command. Please try again." << std::endl;
	}
	return 0;
}
