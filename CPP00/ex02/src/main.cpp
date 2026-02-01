/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 10:44:13 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/02/01 11:45:23 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <time.h>

void	addZero(int time)
{
	if (time >= 10)
		std::cout << time;
	else
		std::cout << "0" << time;
}

int main()
{
	time_t test_rawTime;
	struct tm * timeinfo;

	test_rawTime = time(NULL);
	timeinfo = localtime(&test_rawTime);
	std::cout << "[" << timeinfo->tm_year + 1900;
	addZero(timeinfo->tm_mon + 1);
	addZero(timeinfo->tm_mday);
	std::cout << "_";
	addZero(timeinfo->tm_hour);
	addZero(timeinfo->tm_min);
	addZero(timeinfo->tm_sec);
	std::cout << "] ";
}
