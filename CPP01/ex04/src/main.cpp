/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 14:23:24 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/02/19 13:04:19 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string	replacement(std::string  fileInfo, std::string  s1, std::string  s2)
{
	std::string	replacedInfo;
	size_t		pos;

	pos = fileInfo.find(s1);
	if (pos == std::string::npos)
		return (fileInfo);
	while(pos != std::string::npos)
	{
		replacedInfo = fileInfo.substr(0, pos);
		replacedInfo.append(s2);
		replacedInfo = replacedInfo.append(fileInfo.substr(pos + s1.length()));
		fileInfo = replacedInfo;
		pos = fileInfo.find(s1, pos + s2.length());
	}
	return (replacedInfo);
}

void readFile(std::string  filename, std::string  s1, std::string  s2)
{
	std::string  fileInfo;
	std::ifstream inFile(filename.c_str());
	if (inFile)
	{
		std::ofstream outFile((filename + ".replace").c_str());
		std::stringstream buffer;
		buffer << inFile.rdbuf();
		fileInfo = buffer.str();
		fileInfo = replacement(fileInfo, s1, s2);
		outFile << fileInfo;
	}
	else
	{
		std::cerr<<"Error: Could not open the file.\n";
		return ;
	}
	return ;
}

int main(int argc, char **argv)
{
	std::string  filename;
	std::string  s1;
	std::string  s2;

	if (argc != 4)
	{
		std::cout << "ERROR: Not the correct amount of input;" << std::endl;
		return (0);
	}
	filename = argv[1];
	s1 = argv[2];
	if (s1.empty())
	{
		std::cout << "Error: s1 is empty;" << std::endl;
		return (0);
	}
	s2 = argv[3];
	readFile(filename, s1, s2);
	return 0;
}
