/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:09:23 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/16 19:07:12 by kyaubry          ###   ########.fr       */
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
	if (user->getGetNick() == false)
	{
		std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
		std::map<int, User*>::iterator it;
		bool usernameExists = false;
		do {
			usernameExists = false;
			for (it = UserTab.begin(); it != UserTab.end(); ++it) 
			{
				User* userT = it->second;
				if (message == userT->getNickname())
				{
				usernameExists = true;
				break;
			}
			}
			if (usernameExists)
				message = message + "_";
		} while (usernameExists);
		user->User::setNickname(message);
		user->setGetNick();
	}
	else
	{
		std::cout << "nnnnnnnnnnnnnnnnn" << std::endl;
		std::map<int, User*>::iterator it;
		bool usernameExists = false;
		for (it = UserTab.begin(); it != UserTab.end(); ++it) 
		{
			User* userT = it->second;
			if (message == userT->getNickname())
			{
				usernameExists = true;
				std::string response3 = ":server 433 " + user->getNickname() + " " + message + " :Nickname is already in use\r\n";
				std::cout << "test " << response3 << std::endl;
				send(user->getSocket(), response3.c_str(), response3.size(), 0);
				break;
	
				
			}
		}
		if (usernameExists == false)
		{
			std::string response3 = user->getID() + " NICK " + message + "\r\n";
			user->User::setNickname(message);
			std::cout << "test " << response3 << std::endl;
			send(user->getSocket(), response3.c_str(), response3.size(), 0);
		}
	}
}

void	Server::CommandUSER(User *user, std::string message)
{
	std::istringstream iss(message);
	std::string username, unused, hostname;
	iss >> username >> unused >> hostname;
	user->setUsername(username);
	user->setHostname(hostname);
	std::string response4 = ":localhost 001 " + user->getNickname() +" :Welcome to the IRC server\r\n";
	send(user->getSocket(), response4.c_str(), response4.size(), 0);
}

void Server::CommandJOIN2(User *user, std::string nameChannel, std::string mdp)
{
	std::map<std::string, Channel*>::iterator it;
	for (it = ChannelTab.begin(); it != ChannelTab.end(); ++it)
	{
		std::string name = it->first;
		Channel* channel = it->second;
		if (nameChannel == name)
		{
			channel->Channel::AddUser(user, mdp);
			user->setChannel(nameChannel);
			std::string response4 = user->getID() + " JOIN " + channel->getName() + "\r\n";	
			send(user->getSocket(), response4.c_str(), response4.size(), 0);
			channel->SendMsg(user, response4);
			CommandNAMES(user, channel);
			return ;
		}
	}
	Channel* newChannel = new Channel(nameChannel);
	newChannel->Channel::AddUser(user, "");
	user->setChannel(nameChannel);
	ChannelTab[nameChannel] = newChannel;
	std::string response4 = user->getID() + " JOIN " + newChannel->getName() + "\r\n";
	send(user->getSocket(), response4.c_str(), response4.size(), 0);
	CommandNAMES(user, newChannel);
}

void	Server::CommandJOIN(User *user, std::string message)
{
	std::string chanel;
	std::string mdp;
	std::string::size_type end = message.find(' ');

	if (end == std::string::npos)
	{
		chanel = message;
		mdp = "";
	}
	else
	{
		chanel = message.substr(0, end);
		mdp = message.substr(end + 1);
	}
	std::map<std::string, std::string> map;
	size_t pos1 = 0;
	size_t pos2 = 0;
	
	size_t pos3 = 0;
	size_t pos4 = 0;
	while (1)
	{
		std::string i;
		std::string j;
		pos2 = chanel.find(',', pos1);
		pos4 = mdp.find(',', pos3);
		if (pos2 == std::string::npos){
			i = chanel.substr(pos1);
		}
		else {
			i = chanel.substr(pos1, pos2);
			pos1 = pos2 + 1;
		}
		if (pos4 == std::string::npos){
			j = mdp.substr(pos3);
		}
		else{
			j = mdp.substr(pos3, pos4);
			pos3 = pos4 + 1;
		}
		map[i] = j;
		if (pos2 == std::string::npos)
			break ;
	}
	std::map<std::string, std::string>::iterator it;
	for (it = map.begin(); it != map.end(); ++it)
	{
		CommandJOIN2(user, it->first, it->second);
	}
	/*size_t pos1 = 0;
	size_t pos2 = message.find(',');

	size_t posSpace = message.find(' ');
	
	std::string mdp = message.substr(posSpace);
	size_t pos3 = 0;
	size_t pos4 = mdp.find(',');
	std::map<std::string, Channel*>::iterator it;
	while (1)
	{
		
		std::string nameChannel = message.substr(pos1, pos2);
		if (pos4 >= pos3)
			std::string mdpChannel = "";
		else
			std::string mdpChannel = mdp.substr(pos3, pos4);
		CommandJOIN2(user, nameChannel, mdp);
		pos1 = pos2;
		pos2 += message.find(',');
		pos3 = pos4;
		pos4 += mdp.find(',');
		if (pos2 >= posSpace)
			break ;
		
	}*/
}
/*
size_t pos1 = command.find(' ');
size_t pos2 = command.find(' ', pos1 + 1);
void	Server::CommandJOIN(User *user, std::string message)
{
	std::cout << message << "\n";
	std::map<std::string, Channel*>::iterator it;
	for (it = ChannelTab.begin(); it != ChannelTab.end(); ++it)
	{
		std::string name = it->first;
		Channel* channel = it->second;
		if (message == name)
		{
			channel->Channel::AddUser(user);
			user->setChannel(message);
			std::string response4 = user->getID() + " JOIN " + channel->getName() + "\r\n";	
			send(user->getSocket(), response4.c_str(), response4.size(), 0);
			CommandNAMES(user, channel);
			return;
		}
	}
	Channel* newChannel = new Channel(message);
	newChannel->Channel::AddUser(user);
	user->setChannel(message);
	ChannelTab[message] = newChannel;
	std::string response4 = user->getID() + " JOIN " + newChannel->getName() + "\r\n";
	send(user->getSocket(), response4.c_str(), response4.size(), 0);
	CommandNAMES(user, newChannel);
}*/

void	Server::CommandNAMES(User *user, Channel *channel)
{
	std::string response = ":server 353 " + user->getNickname() + " = " + user->getChannel() + " :" +  user->getNickname() + FindChannel(user->getChannel())->getStringUser(user->getNickname()) + "\r\n";
	send(user->getSocket(), response.c_str(), response.size(), 0);
	std::string response1 = ":server 366 " + user->getNickname() + " " + user->getChannel() + " :End of NAMES list\r\n";
	send(user->getSocket(), response1.c_str(), response1.size(), 0);
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
			channel->SendMsg(user, response4);
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

