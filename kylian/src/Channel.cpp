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

void Channel::AddUser(User *user, std::string mdp)
{
	if (IsHere(user) == true)
		return ;
	this->UserBook.push_back(user);
	if (this->_password != "" && mdp != this->_password)
	{
		std::string response = user->getID() + " :Password incorrect" + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		return ;
	}
	/*std::string response = user->getID() + " JOIN " + this->getName() + "\r\n";
	send(user->getSocket(), response.c_str(), response.size(), 0);
	std::string response2 = ":server 353 " + user->getUsername() + " = " + user->getChannel() + " :" +  user->getUsername() + this->getStringUser() + "\r\n";
	send(user->getSocket(), response2.c_str(), response2.size(), 0);
	std::string response3 = ":server 366 " + user->getUsername() + " " + user->getChannel() + " :End of /NAMES list.\r\n";
	send(user->getSocket(), response3.c_str(), response3.size(), 0);*/
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

std::string Channel::getStringUser(std::string name)
{
	std::string users;
	std::vector<User *>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		if ((*it)->getNickname() != _name)
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

void Channel::SetPassword(std::string password)
{
	this->_password = password;
}

std::string Channel::getPassword(void)
{
	return _password;
}
