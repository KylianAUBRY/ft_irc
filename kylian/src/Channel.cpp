/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:03:01 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/16 18:36:15 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"

Channel::Channel(std::string name) : _name(name)
{
	this->_password = "";
}

Channel::~Channel()
{
}

std::string Channel::getName(void)
{
	return (_name);
}

void Channel::AddUser(User *user, std::string mdp, int super)
{
	if (IsHere(user) == true)
		return ;
	if (this->_password != "" && mdp != this->_password)
	{
		std::string response = user->getID() + " :Password incorrect" + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		return ;
	}
	this->UserBook[user] = super;
	std::cout << "test " << user->getNickname() << super << "\n";
}

void  Channel::DelUser(User *user)
{
	std::map<User*, int>::iterator it = UserBook.find(user);
	if (it != UserBook.end())
	{
		UserBook.erase(it);
	}
}

std::string Channel::getStringUser(std::string name)
{
	std::string users;
	std::map<User*, int>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		if (it->first->getNickname() != name)
		{
			if (it->second == 0)
				users += " " + it->first->getNickname();
			else if (it->second == 1)
				users += " @" + it->first->getNickname();
		}
		else if (it->first->getNickname() == name)
		{
			if (it->second == 0)
				users = it->first->getNickname() + users;
			else if (it->second == 1)
				users = "@" + it->first->getNickname() + users;
		}
	}
	return users;
}

void Channel::SendMsg(User *user, std::string message)
{
	std::map<User*, int>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		if (it->first->getSocket() != user->getSocket())
			send(it->first->getSocket(), message.c_str(), message.size(), 0);
	}
}


bool Channel::IsHere(User *user)
{
	std::map<User*, int>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		if (it->first->getSocket() == user->getSocket())
			return true;
	}
	return false;
}

void Channel::SetPassword(std::string password)
{
	this->_password = password;
}

std::string Channel::getPassword(void)
{
	return _password;
}

bool Channel::isEmpty()
{
	if (UserBook.empty())
		return true;
	return false;
}
