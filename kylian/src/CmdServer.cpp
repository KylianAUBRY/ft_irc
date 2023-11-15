/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:09:23 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/15 19:59:29 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void	Server::CommandCAP(User *user)
{
	std::string capabilities = "sasl";
	std::string response = "CAP * LS :" + capabilities + "\r\n";
	send(user->getSocket(), response.c_str(), response.size(), 0);
}

void	Server::CommandPASS(User *user)
{
	/*std::string response2 = ":localhost 001 "+ user->getUsername() +" :Welcome to the IRC server\r\n";
	send(user->getSocket(), response2.c_str(), response2.size(), 0);*/
}

void	Server::CommandNICK(User *user, std::string message)
{
	std::map<int, User*>::iterator it;
	bool usernameExists = false;
	do {
	    usernameExists = false;
	    for (it = UserTab.begin(); it != UserTab.end(); ++it) {
		User* userT = it->second;
		if (message == userT->getNickname()) {
		    usernameExists = true;
		    break;
		}
	    }
	    if (usernameExists) {
		message = message + "_";
	    }
	} while (usernameExists);
	user->User::setNickname(message);
	/*std::string response3 = ":mlangloi!mlangloi@host mlangloi :mlangloi\r\n";
	send(user->getSocket(), response3.c_str(), response3.size(), 0);*/
}

void	Server::CommandUSER(User *user, std::string message)
{
	std::istringstream iss(message);
	std::string username, unused, hostname;
	iss >> username >> unused >> hostname;
	user->setUsername(username);
	user->setHostname(hostname);
	std::string response4 = ":localhost 001 " + user->getUsername() +" :Welcome to the IRC server\r\n";
	send(user->getSocket(), response4.c_str(), response4.size(), 0);
}

void	Server::CommandJOIN(User *user, std::string message)
{
	std::map<std::string, Channel*>::iterator it;
	for (it = ChannelTab.begin(); it != ChannelTab.end(); ++it)
	{
		std::string name = it->first;
		Channel* channel = it->second;
		if (message == name)
		{
			channel->Channel::AddUser(user);
			user->setChannel(message);
			std::string response4 = ":" + user->getID() + " JOIN " + channel->getName() + "\r\n";	
			send(user->getSocket(), response4.c_str(), response4.size(), 0);
			CommandNAMES(user);
			return;
		}
	}
	Channel* newChannel = new Channel(message);
	newChannel->Channel::AddUser(user);
	user->setChannel(message);
	ChannelTab[message] = newChannel;
	std::string response4 = ":" + user->getID() + " JOIN " + newChannel->getName() + "\r\n";
	send(user->getSocket(), response4.c_str(), response4.size(), 0);
	CommandNAMES(user);
}

void	Server::CommandNAMES(User *user)
{
	std::cout << "list : " << FindChannel(user->getChannel())->getStringUser() << std::endl;
	std::string response4 = ":server 353 " + user->getUsername() + " = " + user->getChannel() + " :" +  user->getUsername() + FindChannel(user->getChannel())->getStringUser() + "\r\n";
	send(user->getSocket(), response4.c_str(), response4.size(), 0);
	response4 = ":server 366 " + user->getUsername() + " " + user->getChannel() + " :End of /NAMES list.\r\n";
	send(user->getSocket(), response4.c_str(), response4.size(), 0);
	
}

void	Server::CommandPRIVMSG(User *user, std::string message)
{
	size_t Pos = message.find(':');
    std::string mes = message.substr(Pos + 1);
    message = message.substr(0, Pos - 1);
	std::map<std::string, Channel*>::iterator it;
	for (it = ChannelTab.begin(); it != ChannelTab.end(); ++it)
	{
		std::string name = it->first;
		std::cout << message << " " << name << std::endl;
		Channel* channel = it->second;
		if (message == name)
		{
			SendMessage(user, channel, mes);
			return;
		}
	}
}

void	Server::CommandPART(User *user, std::string message)
{
	std::map<std::string, Channel*>::iterator it;
	for (it = ChannelTab.begin(); it != ChannelTab.end(); ++it)
	{
		std::string name = it->first;
		Channel* channel = it->second;
		if (message == name)
		{
			channel->DelUser(user);
			std::string response4 = user->getID() + " PART " + channel->getName() + " :" + user->getNickname() + "\r\n";
			send(user->getSocket(), response4.c_str(), response4.size(), 0);
			user->setChannel("");
			return;
		}
	}
}

Channel	*Server::FindChannel(std::string search)
{
	std::map<std::string, Channel*>::iterator it;
	for (it = ChannelTab.begin(); it != ChannelTab.end(); ++it)
	{
		std::string name = it->first;
		Channel* channel = it->second;
		if (search == name)
		{
			return(channel);
		}
	}
	return(NULL);
}

void	Server::SendMessage(User *user, Channel *channel, std::string mes)
{
	if (channel->IsHere(user) == false)
		return ;
	std::string response4 = ":" + user->getNickname() + " PRIVMSG " + channel->getName() + " :" + mes + "\r\n";
	channel->SendMsg(user, response4);
	/*std::map<int, User*>::iterator it;
	for (it = UserTab.begin(); it != UserTab.end(); ++it)
	{
		User* test = it->second;
		if (test->getSocket() != user->getSocket())
			send(test->getSocket(), response4.c_str(), response4.size(), 0);
		
	}*/
}

