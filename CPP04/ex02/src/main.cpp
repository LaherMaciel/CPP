/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:14:15 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/03/24 17:16:20 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Animal.hpp"
#include "../include/Dog.hpp"
#include "../include/Cat.hpp"
#include "../include/WrongAnimal.hpp"
#include "../include/WrongCat.hpp"
#include "../include/Brain.hpp"

#include <iostream>

int main()
{
	const Animal *meta[10];
	for (int i = 0; i < 10; i++)
	{
		if (i < 5)
			meta[i] = new Dog();
		else
			meta[i] = new Cat();
	}
	std::cout << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << meta[i]->getType() << " " << std::endl;
		meta[i]->makeSound();
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < 10; i++)
		delete(meta[i]);
	std::cout << std::endl;
	Dog dog1;
	dog1.getBrain()->setIdea("original idea", 0);
	std::cout << std::endl;

	Dog dog2(dog1);
	std::cout << dog2.getBrain()->getIdea(0) << std::endl;

	dog2.getBrain()->setIdea("changed", 0);
	std::cout << std::endl;
	std::cout << dog1.getBrain()->getIdea(0) << std::endl;
	std::cout << dog2.getBrain()->getIdea(0) << std::endl;
	std::cout << std::endl;
	dog1 = dog2;
	std::cout << std::endl;
	std::cout << dog1.getBrain()->getIdea(0) << std::endl;
	std::cout << dog2.getBrain()->getIdea(0) << std::endl;
	std::cout << std::endl;

	/* const Animal* meta2 = new Animal();
	meta2->makeSound();
	delete(meta2); */
	return (0);
}
