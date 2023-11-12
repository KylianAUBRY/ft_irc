/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:09:57 by mlangloi          #+#    #+#             */
/*   Updated: 2023/11/09 19:09:58 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Channel.hpp"

std::map<std::string, Channel*> Channel::ChannelBook;
std::vector<User*> Channel::UserBook;

Channel::Channel()
{
}

Channel::Channel(std::string name) : name(name)
{
	this->ChannelBook[name] = this;
	std::cout << "creation du channel : " << name << std::endl;
}

Channel::~Channel()
{
}

std::string Channel::getName()
{
	return (this->name);
}

std::string Channel::getStringUser()
{
	std::string users;
	std::vector<User*>::iterator it;
	for (it = UserBook.begin(); it != UserBook.end(); ++it)
	{
		users = users + " " + (*it)->getUsername();
	}
	return (users);
}

Channel *FindChannel(std::string search)
{
	std::map<std::string, Channel*>::iterator it;
	for (it = Channel::ChannelBook.begin(); it != Channel::ChannelBook.end(); ++it)
	{
		std::string name = it->first;
		Channel* channel = it->second;
		if (search == name)
		{
			return (channel);
		}
	}
	return (NULL);
}

void Channel::AddUser(User *user)
{
	UserBook.push_back(user);
}

void JoinChannel(User *user, std::string search)
{
	std::map<std::string, Channel*>::iterator it;
	for (it = Channel::ChannelBook.begin(); it != Channel::ChannelBook.end(); ++it)
	{
		std::string name = it->first;
		Channel* channel = it->second;
		if (search == name)
		{
			channel->Channel::AddUser(user);
		}
	}
	Channel* newChannel = new Channel(search);
	newChannel->Channel::AddUser(user);
	user->setChannel(search);
	std::cout << "nb : " << Channel::UserBook.size() << std::endl;
}
