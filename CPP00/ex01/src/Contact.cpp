/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:13:33 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/01/30 16:45:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Contact.hpp"

void	Contact::set_first_name(std::string fname)
{
	first_name = fname;
}

void	Contact::set_last_name(std::string lname)
{
	last_name = lname;
}

void	Contact::set_nickname(std::string nname)
{
	nickname = nname;
}

void	Contact::set_phone_number(std::string pnumber)
{
	phone_number = pnumber;
}

void	Contact::set_darkest_secret(std::string secret)
{
	darkest_secret = secret;
}

std::string	Contact::get_first_name() const
{
	return first_name;
}

std::string	Contact::get_last_name() const
{
	return last_name;
}

std::string	Contact::get_nickname() const
{
	return nickname;
}

std::string	Contact::get_phone_number() const
{
	return phone_number;
}

std::string	Contact::get_darkest_secret() const
{
	return darkest_secret;
}