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

std::map<std::string, Channel> Channel::ChannelBook;

Channel::Channel()
{
}

Channel::Channel(std::string name) : name(name)
{
	this->ChannelBook[name] = *this;
	std::cout << "creation du channel : " << name << std::endl;
}

Channel::~Channel()
{
}

std::string Channel::getName()
{
	return (this->name);
}

int FindChannel(std::string search)
{
	std::map<std::string, Channel>::iterator it;
	for (it = Channel::ChannelBook.begin(); it != Channel::ChannelBook.end(); ++it)
	{
		std::string name = it->first;
		Channel channel = it->second;
		if (search == name)
		{
			std::cout << "Nom du canal : " << name << std::endl;
			return (1);
		}
	}
	std::cout << "Canal introuvable " << std::endl;
	return (0);
}

void Channel::AddUser(User user)
{
	UserBook.push_back(user);
	std::cout << "user : " << user.getUsername() << " ajoute au channel : " << this->getName() << std::endl;
}

void JoinChannel(User user, std::string search)
{
	std::map<std::string, Channel>::iterator it;
	for (it = Channel::ChannelBook.begin(); it != Channel::ChannelBook.end(); ++it)
	{
		std::string name = it->first;
		Channel channel = it->second;
		if (search == name)
		{
			channel.Channel::AddUser(user);
		}
	}
	std::cout << "channel introuvable, creation\n";
	Channel newChannel(search);
	newChannel.Channel::AddUser(user);
}
