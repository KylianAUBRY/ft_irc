/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:42:01 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/15 12:11:43 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/User.hpp"

User::User(int socket) : _socket(socket)
{
	_username = "";
	_channel = "";
	_nickname = "";
	_hostname = "";
}

User::~User()
{
	close(this->_socket);
}

std::string User::getUsername(void)
{
	return (_username);
}

std::string User::getNickname(void)
{
	return (_nickname);
}

std::string User::getChannel(void)
{
	return (_channel);
}

std::string User::getHostname(void)
{
	return (_hostname);
}

int User::getSocket(void)
{
	return (_socket);
}

std::string User::getID(void)
{
	std::string ID = ":" + this->_nickname + "!" + this->_username + "@" + this->_hostname;
	return (ID);
}

void User::setUsername(std::string username)
{
	this->_username = username;
}

void User::setNickname(std::string nickname)
{
	this->_nickname = nickname;
}

void User::setHostname(std::string hostname)
{
	this->_hostname = hostname;
}

void User::setChannel(std::string channel)
{
	this->_channel = channel;
}

