/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 18:40:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/21 21:30:19 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange
{
	public:
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange const& other);
		~BitcoinExchange(void);
		BitcoinExchange&	operator=(BitcoinExchange const& other);

		void	loadDatabase(std::string const& path);
		void	processInput(std::string const& path);

	private:
		std::map<std::string, double>	_rates;

		double	getRate(std::string const& date) const;
};

void		validateDate(std::string const& date);
std::string	trim(std::string const& s);

#endif
