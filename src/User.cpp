/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:42:01 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/24 17:46:00 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/User.hpp"

User::User(int socket) : _socket(socket)
{
	this->_isDown = 0;
	_buffCommand = "";
	_username = "";
	_channel = "";
	_nickname = "";
	_hostname = "";
	_getNick = false;
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

bool User::getGetNick(void)
{
	return (_getNick);
}

std::string User::getID(void)
{
	std::string ID = ":" + this->_nickname + "!" + this->_username + "@" + this->_ip;
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

void User::setGetNick()
{
	this->_getNick = true;
}

std::string User::getbuffCommand()
{
	return this->_buffCommand;
}

void User::setbuffCommand(std::string command)
{
	this->_buffCommand = command;
}

void User::joinbuffCommand(std::string command)
{
	this->_buffCommand += command;
}

int User::getisDown(void)
{
	return this->_isDown;
}

void User::setisDown(int down)
{
	this->_isDown = down;
}

void User::incrementisDown()
{
	this->_isDown ++;
}

std::string User::getIp(void)
{
	return this->_ip;
}

void User::setIp(std::string ip)
{
	this->_ip = ip;
}