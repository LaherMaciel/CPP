/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:12:57 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/01/31 19:42:20 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PhoneBook.hpp"
#include <ios>
#include <iostream>
#include <iomanip>
#include <cstdlib>


PhoneBook::PhoneBook()
{
	total_contacts = 0;
	next_index = 0;
}

static std::string get_input(std::string prompt)
{
	std::string input;
	do
	{
		std::cout << prompt;
		std::getline(std::cin, input);
	} while (input.empty());
	return input;
}

void	PhoneBook::add_contact()
{
	std::string input;

	input = get_input("Enter first name: ");
	contacts[next_index].set_first_name(input);
	
	input = get_input("Enter last name: ");
	contacts[next_index].set_last_name(input);
	
	input = get_input("Enter nickname: ");
	contacts[next_index].set_nickname(input);

	input = get_input("Enter phone number: ");
	contacts[next_index].set_phone_number(input);
	
	input = get_input("Enter darkest secret: ");
	contacts[next_index].set_darkest_secret(input);

	if (total_contacts < 8)
		total_contacts++;
	next_index++;
	if (next_index >= 8)
		next_index = 0;
}

static std::string format_field(std::string field)
{
	if (field.length() >= 10)
		return field.substr(0, 9) + ".";
	else
		return field;
}

static void	display_contact(Contact contacts[], int total_contacts)
{
	int			i;

	i = 0;
	std::cout << "|" << std::right << std::setw(10) << "index" << "|" << 
		std::setw(10) << "first name" << "|" << 
		std::setw(10) << "last name" << "|" << 
		std::setw(10) << "nickname" << "|" << std::endl;
	while (i < total_contacts)
	{
		std::cout << "|" << std::right << std::setw(10) << i << "|" <<
			std::setw(10) << format_field(contacts[i].get_first_name()) << "|" <<
			std::setw(10) << format_field(contacts[i].get_last_name()) << "|" <<
			std::setw(10) << format_field(contacts[i].get_nickname()) << "|" << std::endl;
		i++;
	}
}

static void user_info(Contact contact)
{
	std::cout << "First Name: " << contact.get_first_name() << std::endl;
	std::cout << "Last Name: " << contact.get_last_name() << std::endl;
	std::cout << "Nickname: " << contact.get_nickname() << std::endl;
	std::cout << "Phone Number: " << contact.get_phone_number() << std::endl;
	std::cout << "Darkest Secret: " << contact.get_darkest_secret() << std::endl;
}

void PhoneBook::search_contacts()
{
	int 		index;
	std::string	input;

	display_contact(contacts, total_contacts);
	std:: cout << "Enter index to view details: ";
	std::getline(std::cin, input);
	if (input.length() != 1 || !std::isdigit(input[0]))
	{
		std::cout << "Invalid index." << std::endl;
		return ;
	}
	index = atoi(input.c_str());
	if (index < 0 || index >= total_contacts)
	{
		std::cout << "Index out of range." << std::endl;
		return ;
	}
	user_info(contacts[index]);
}