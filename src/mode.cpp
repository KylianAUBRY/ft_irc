/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:23:04 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/24 17:45:43 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void 	Server::ModeK(User *user, Channel *channel, std::string message, int i)
{
	if (channel->isOp(user->getNickname()) == 0)
	{
		std::string response = ":server 482 " + user->getNickname() + " " + channel->getName() + " :You're not channel operator\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
	}
	else if (channel->getMode('k') == false && i == 0)
	{
		channel->SetPassword(message);
		channel->SetMode('k', true);
		std::string response = user->getID() + " MODE " + channel->getName() + " +k " + message + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user, response);
	}
	else if (channel->getMode('k') == true && i == 0)
	{
		channel->SetPassword(message);
		std::string response = user->getID() + " MODE " + channel->getName() + " +k " + message + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user, response);
	}
	else if (channel->getMode('k') == true && i == 1)
	{
		channel->SetPassword("");
		channel->SetMode('k', false);
		std::string response = user->getID() + " MODE " + channel->getName() + " -k\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user, response);
	}
}

void 	Server::ModeI(User *user, Channel *channel, int i)
{
	if (channel->isOp(user->getNickname()) == 0)
	{
		std::string response = ":server 482 " + user->getNickname() + " " + channel->getName() + " :You're not channel operator\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
	}
	else if (channel->getMode('i') == false && i == 0)
	{
		channel->SetMode('i', true);
		std::string response = user->getID() + " MODE " + channel->getName() + " +i " + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user ,response);
	}
	else if (channel->getMode('i') == true && i == 1)
	{
		channel->SetMode('i', false);
		std::string response = user->getID() + " MODE " + channel->getName() + " -i " + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user ,response);
	}
}

void 	Server::ModeO(User *user, Channel *channel, std::string message, int i)
{
	if (channel->isOp(user->getNickname()) == 0)
	{
		std::string response = ":server 482 " + user->getNickname() + " " + channel->getName() + " :You're not channel operator\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
	}
	else if (i == 0 && channel->isOp(message) == 0)
	{
		channel->changeOp(message, 1);
		std::string response = user->getID() + " MODE " + channel->getName() + " +o " + message + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user, response);
	}
	else if (i == 1 && channel->isOp(message) == 1)
	{
		channel->changeOp(message, 0);
		std::string response = user->getID() + " MODE " + channel->getName() + " -o " + message + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user, response);
	}
}

void 	Server::ModeT(User *user, Channel *channel, int i)
{
	if (channel->isOp(user->getNickname()) == 0)
	{
		std::string response = ":server 482 " + user->getNickname() + " " + channel->getName() + " :You're not channel operator\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
	}
	else if (channel->getMode('t') == false && i == 0)
	{
		channel->SetMode('t', true);
		std::string response = user->getID() + " MODE " + channel->getName() + " +t " + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user ,response);
		
	}
	else if (channel->getMode('t') == true && i == 1)
	{
		channel->SetMode('t', false);
		std::string response = user->getID() + " MODE " + channel->getName() + " -t " + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user ,response);
	}
}

void 	Server::ModeL(User *user, Channel *channel, std::string message, int i)
{
	if (i == 0 && message.length() <= 0)
		return ;
	for (std::string::const_iterator it = message.begin(); it != message.end(); ++it)
	{
		if (!std::isdigit(static_cast<unsigned char>(*it)))
			return;
	}
	if (message.length() > 10)
		return;
	if (i == 0 && stoll(message) > std::numeric_limits<int>::max())
		return;
	if (channel->isOp(user->getNickname()) == 0)
	{
		std::string response = ":server 482 " + user->getNickname() + " " + channel->getName() + " :You're not channel operator\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
	}
	else if (channel->getMode('l') == false && i == 0)
	{
		int nb = stoi(message);
		channel->SetMode('l', true);
		channel->SetUserLimit(nb);
		std::string response = user->getID() + " MODE " + channel->getName() + " +l " + message + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user ,response);
		
	}
	else if (channel->getMode('l') == true && i == 0)
	{
		int nb = stoi(message);
		channel->SetUserLimit(nb);
		std::string response = user->getID() + " MODE " + channel->getName() + " +l " + message + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user ,response);
	}
	else if (channel->getMode('l') == true && i == 1)
	{
		channel->SetMode('l', false);
		channel->SetUserLimit(0);
		std::string response = user->getID() + " MODE " + channel->getName() + " -l\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user ,response);
	}
}
