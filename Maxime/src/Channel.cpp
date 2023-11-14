/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:03:01 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/14 15:03:12 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"

Channel::Channel(std::string name) : _name(name)
{
}

Channel::~Channel()
{
}

std::string Channel::getName(void)
{
	return (_name);
}

void Channel::AddUser(std::string user)
{
	this->UserBook.push_back(user);
}

std::string Channel::getStringUser()
{
	std::string users;
	std::vector<std::string>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		users = users + " " + *it;
	}
	return (users);
}
