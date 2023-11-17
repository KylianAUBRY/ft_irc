/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:09:23 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/17 17:49:51 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void	Server::CommandCAP(User *user)
{
	std::string capabilities = "sasl";
	std::string response = "CAP * LS :" + capabilities + "\r\n";
	send(user->getSocket(), response.c_str(), response.size(), 0);
}

int	Server::CommandPASS(User *user, std::string pass)
{
	if (pass != this->_password)
	{
		std::string response2 = ":server 464 " + user->getNickname() + " :Password incorrect\r\n";
		send(user->getSocket(), response2.c_str(), response2.size(), 0);
		return (1);
	}	
	else
	{
		std::string response2 = ":localhost 001 "+ user->getNickname() +" :Password Correct\r\n";
		send(user->getSocket(), response2.c_str(), response2.size(), 0);
		return (0);
	}
}

void	Server::CommandNICK(User *user, std::string message)
{
	if (user->getGetNick() == false)
	{
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
		std::map<int, User*>::iterator it;
		bool usernameExists = false;
		for (it = UserTab.begin(); it != UserTab.end(); ++it) 
		{
			User* userT = it->second;
			if (message == userT->getNickname())
			{
				usernameExists = true;
				std::string response3 = ":server 433 " + user->getNickname() + " " + message + " :Nickname is already in use\r\n";
				send(user->getSocket(), response3.c_str(), response3.size(), 0);
				break;
			}
		}
		if (usernameExists == false)
		{
			std::string response3 = user->getID() + " NICK " + message + "\r\n";
			user->User::setNickname(message);
			send(user->getSocket(), response3.c_str(), response3.size(), 0);
		}
	}
}

void	Server::CommandUSER(User *user, std::string message, int passOK)
{
	if (passOK == 0)
	{
		std::istringstream iss(message);
		std::string username, unused, hostname;
		iss >> username >> unused >> hostname;
		user->setUsername(username);
		user->setHostname(hostname);
		std::string response4 = ":localhost 001 " + user->getNickname() +" :Welcome to the IRC server\r\n";
		send(user->getSocket(), response4.c_str(), response4.size(), 0);
	}
	else if (passOK == 1)
	{
		std::string response4 = ":server 462 " + user->getNickname() + " :You may not reregister\r\n";
		send(user->getSocket(), response4.c_str(), response4.size(), 0);
	}
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
			channel->Channel::AddUser(user, mdp, 0);
			user->setChannel(nameChannel);
			std::string response4 = user->getID() + " JOIN " + channel->getName() + "\r\n";	
			send(user->getSocket(), response4.c_str(), response4.size(), 0);
			channel->SendMsg(user, response4);
			CommandNAMES(user, channel);
			return;
		}
	}
	Channel* newChannel = new Channel(nameChannel);
	newChannel->Channel::AddUser(user, "", 1);
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
		if (pos2 == std::string::npos)
			i = chanel.substr(pos1);
		else {
			i = chanel.substr(pos1, pos2);
			pos1 = pos2 + 1;
		}
		if (pos4 == std::string::npos)
			j = mdp.substr(pos3);
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
}

void	Server::CommandNAMES(User *user, Channel *channel)
{
	std::string response = ":server 353 " + user->getNickname() + " = " + user->getChannel() + " :" +  FindChannel(user->getChannel())->getStringUser(user->getNickname()) + "\r\n";
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
			if (channel->isEmpty() == true)
			{
				delete channel;
				ChannelTab.erase(it);
			}
			std::string response4 = user->getID() + " PART " + channel->getName() + " :" + user->getNickname() + "\r\n";
			send(user->getSocket(), response4.c_str(), response4.size(), 0);
			channel->SendMsg(user, response4);
			user->setChannel("");
			return;
		}
	}
}

void	Server::CommandMODE2(User *user, char cha, int status, std::string supmode, std::string nameChannel)
{
	std::map<std::string, Channel*>::iterator it;
	for (it = ChannelTab.begin(); it != ChannelTab.end(); ++it)
	{
		std::string name = it->first;
		Channel* channel = it->second;
		if (nameChannel == name)
		{
			switch (cha)
			{
				case 'k':
					ModeK(user, channel, supmode, status);
					break ;
				case 't':
					ModeT(user, channel, status);
					break;
			}
		}
	}
}

void	Server::CommandMODE(User *user, std::string message)
{
	std::string mode;
	std::string supmode;
	std::string chanel;
	size_t end = message.find(' ');
	if (end == std::string::npos)
		return ;
	chanel = message.substr(0, end);
	message = message.substr(end + 1);
	end = message.find(' ');
	if (end == std::string::npos)
	{
		mode = message;
		supmode = "";
	}
	else
	{
		mode = message.substr(0, end);
		supmode = message.substr(end + 1);
	}
	int i = -1;
	int status = 0;
	size_t pos1 = 0;
	size_t pos2 = supmode.find(' ');
	// k o l 

	// i t 
	while (++i < mode.size())
	{
		if (mode[i] == '+')
		{
			status = 0;
			continue;
		}
		else if (mode[i] == '-')
		{
			status = 1;
			continue;
		}
		if (mode[i] == 'i' || mode[i] == 't' || mode[i] == 'k' || mode[i] == 'o' || mode[i] == 'l')
		{
			if (mode[i] == 'i' || mode[i] == 't')
			{
				CommandMODE2(user, mode[i], status, "", chanel);
				continue;
			}
			if (pos2 == std::string::npos)
				CommandMODE2(user, mode[i], status, supmode.substr(pos1), chanel);
			else{
				CommandMODE2(user, mode[i], status, supmode.substr(pos1, pos2), chanel);
				pos1 = pos2 + 1;
			}
		}
		else
			continue;
		size_t pos2 = supmode.find(' ', pos1);
	}
}

void	Server::CommandTOPIC(User *user, std::string message)
{
	std::string chanel;
	size_t end = message.find(' ');
	if (end == std::string::npos)
		return ;
	chanel = message.substr(0, end);
	std::map<std::string, Channel*>::iterator it;
	for (it = ChannelTab.begin(); it != ChannelTab.end(); ++it)
	{
		std::string name = it->first;
		Channel* channel = it->second;
		if (chanel == name)
		{
			if (channel->getMode('t') == false)
			{
				std::string response = user->getID() + " TOPIC " + channel->getName() + " :" + message.substr(end) + "\r\n";
				send(user->getSocket(), response.c_str(), response.size(), 0);
				channel->SendMsg(user ,response);
			}
			else
			{
				std::string response = ":server 482 " + user->getNickname() + " " + channel->getName() + " :You do not have access to change the topic on this channel" + "\r\n";
				send(user->getSocket(), response.c_str(), response.size(), 0);
			}
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

