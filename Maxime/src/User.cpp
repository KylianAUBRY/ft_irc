/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:54:33 by mlangloi          #+#    #+#             */
/*   Updated: 2023/10/27 17:54:33 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"User.hpp"

User::User()
{
}

User::User(int socket, int num) : socket(socket), num(num)
{
	std::cout << "User cree : " << this->username << this->socket << std::endl;
}

User::~User()
{
}

int User::getSocket()
{
	return (this->socket);
}

int User::getNum()
{
	return (this->num);
}

std::string User::getUsername()
{
	return (this->username);
}

std::string User::getChannel()
{
	return (this->channel);
}

void User::setUsername(std::string name)
{
	this->username = name;
}

void User::setChannel(std::string newChannel)
{
	this->channel = newChannel;
}


