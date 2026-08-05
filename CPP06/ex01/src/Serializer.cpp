/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 13:25:41 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/08/03 17:52:34 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

uintptr_t	Serializer::serialize(Data* dataPtr)
{
	return (reinterpret_cast<uintptr_t>(dataPtr));
}

Data*	Serializer::deserialize(uintptr_t rawAddress)
{
	return (reinterpret_cast<Data *>(rawAddress));
}
