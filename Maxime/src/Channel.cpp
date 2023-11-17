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
	this->_modeK = false;
}

Channel::~Channel()
{
}

std::string Channel::getName(void)
{
	return (_name);
}

std::string Channel::getPassword(void)
{
	return (_password);
}

void Channel::AddUser(User *user, std::string mdp, int super)
{
	if (IsHere(user) == true)
		return ;
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

bool Channel::isEmpty()
{
	if (UserBook.empty())
		return true;
	return false;
}

void Channel::SetMode(char mode, bool x)
{
    switch (mode) 
    {
        case 'k':
            this->_modeK = x;
            break;
        case 'i':
            // Traitement pour le mode 'i'
            break;
        case 't':
            // Traitement pour le mode 't'
            break;
        case 'o':
            // Traitement pour le mode 'o'
            break;
        case 'l':
            // Traitement pour le mode 'l'
            break;
        default:
            // Code à exécuter par défaut si le mode n'est pas l'un des cas précédents
            break;
    }
}

bool Channel::getMode(char mode)
{
	std::cout << "get\n";
	switch (mode) 
	{
        case 'k':
           return (this->_modeK);
        case 'i':
            // Traitement pour le mode 'i'
            break;
        case 't':
            // Traitement pour le mode 't'
            break;
        case 'o':
            // Traitement pour le mode 'o'
            break;
        case 'l':
            // Traitement pour le mode 'l'
            break;
        default:
            // Code à exécuter par défaut si le mode n'est pas l'un des cas précédents
            break;
    }
}
