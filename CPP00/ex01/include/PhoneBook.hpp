/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:09:16 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/01/30 17:00:47 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP
# include "Contact.hpp"

class PhoneBook
{
	private:
		Contact	contacts[8];
		int		total_contacts;
		int		next_index;

	public:
		PhoneBook();
		void add_contact();
		void search_contacts();
};

#endif // PHONEBOOK_HPP