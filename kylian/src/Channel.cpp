/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:03:01 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/15 19:35:37 by kyaubry          ###   ########.fr       */
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

void Channel::AddUser(User *user)
{
	this->UserBook.push_back(user);
}

void  Channel::DelUser(User *user)
{
	UserBook.erase(std::remove(UserBook.begin(), UserBook.end(), user),UserBook.end());
	std::vector<User *>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		std::cout << (*it)->getNickname() << '\n';
	}
}

std::string Channel::getStringUser()
{
	std::string users;
	std::vector<User *>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		users += " " + (*it)->getNickname();
	}
	return (users);
}

void Channel::SendMsg(User *user, std::string message)
{
	std::vector<User *>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		if ((*it)->getSocket() != user->getSocket())
			send((*it)->getSocket(), message.c_str(), message.size(), 0);
		
	}
}

bool Channel::IsHere(User *user)
{
	std::vector<User *>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		if ((*it)->getSocket() == user->getSocket())
			return true ;
	}
	return false;
}