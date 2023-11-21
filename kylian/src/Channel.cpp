/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:03:01 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/20 11:22:25 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"

Channel::Channel(std::string name) : _name(name)
{
	this->_password = "";
	this->_modeK = false;
	this->_modeT = true;
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
	
	this->UserBook[user] = super;
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

void Channel::SetMode(char mode, bool x)
{
    switch (mode) 
    {
        case 'k':
            this->_modeK = x;
            break;
        case 'i':
            this->_modeI = x;
            break;
        case 't':
            this->_modeT = x;
            break;
        case 'l':
            this->_modeL = x;
            break;
        default:
            break;
    }
}

bool Channel::getMode(char mode)
{
	switch (mode) 
	{
        case 'k':
           return (this->_modeK);
        case 'i':
           return (this->_modeI);
            break;
        case 't':
            return (this->_modeT);
            break;
        case 'l':
            return (this->_modeL);
            break;
        default:
            break;
    }
    	return false;
}


int Channel::isOp(std::string nickname)
{
	std::map<User*, int>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		if (it->first->getNickname() == nickname)
		{
			return (it->second);
		}
	}
	return (0);
}

void Channel::changeOp(std::string nickname, int op)
{
	std::map<User*, int>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		if (it->first->getNickname() == nickname)
		{
			it->second = op;
		}
	}
}

void Channel::SetUserLimit(int limit)
{
	this->_userLimit = limit;
}

int Channel::getNbUser()
{
	int i = 0;
	std::map<User*, int>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		i++;
	}
	return (i);
}

bool Channel::isPlace()
{
	if (this->getNbUser() < this->_userLimit)
		return true;
	return false; 
}

bool Channel::IsInvite(User *user)
{
    for (std::vector<User*>::iterator it = UserInvite.begin(); it != UserInvite.end(); ++it)
    {
        if ((*it)->getSocket() == user->getSocket())
            return true;
    }
    return false;
}

void Channel::addUserInvite(User *user)
{
    if (IsInvite(user))
        return;
    UserInvite.push_back(user);
}
