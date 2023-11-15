/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:40:59 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/14 16:50:04 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

bool Server::Server_start()
{
	int opt = 1;
	try {
		poll_fds = new std::vector<pollfd>( SOMAXCONN + 1 );
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "Error\nMemory allocation error : " << e.what() << std::endl;
		return false;
	}
	if ((this->SServer.fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cout << "Error\nSocket creation failed." << '\n';
		return false;
	}
	if (setsockopt(this->SServer.fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))
		|| setsockopt(this->SServer.fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		std::cout << "Error\nSocket creation failed." << '\n';
		return false;
	}
	this->SServer.info.sin_family = AF_INET;
	this->SServer.info.sin_addr.s_addr = INADDR_ANY;
	this->SServer.info.sin_port = htons(this->_port);
	if (bind(this->SServer.fd, (const struct sockaddr *)&this->SServer.info, sizeof(this->SServer.info)) == -1)
	{
		std::cout << "Error\nSocket binding failed." << '\n';
		return false;
	}
	if (listen(this->SServer.fd, 1) == -1)
	{
		std::cout << "Error\nListen error." << '\n';
		return false;
	}
	this->numConnection = 0;
	return true;
}

void	Server::ConnectClient()
{
	std::vector<pollfd> &client_fds = *poll_fds;
	if (client_fds[0].revents & POLLIN)
	{
		socklen_t csize = sizeof(this->SClient.info);
		this->SClient.fd = accept(this->SServer.fd, (struct sockaddr *)&this->SClient.info, &csize);
		if (this->SClient.fd == -1)
		{
			perror("accept");
			close(this->SServer.fd);
			return ;
		}
		std::cout << "New client connected: " << this->SClient.fd << std::endl;
		try
		{
			User *user = new User(this->SClient.fd);
			UserTab[this->numConnection] = user;
			client_fds[this->numConnection + 1].fd = this->SClient.fd;
			client_fds[this->numConnection + 1].events = POLLIN | POLLOUT;
			this->numConnection++;
		}
		catch (const std::bad_alloc& e)
		{
			std::cerr << "Error\nMemory allocation error : " << e.what() << std::endl;
		}
	}
}

bool Server::Server_loop()
{
	std::vector<pollfd> &client_fds = *poll_fds;
	client_fds[0].fd = this->SServer.fd;
	client_fds[0].events = POLLIN;
	while (1)
	{
		int num_ready = poll(client_fds.data(), this->numConnection + 1, 1000000); // a ajuster le time 
		/*if ( num_ready < 0 )//&& Stop == 1 )
			std::cout << "\nServer: Poll error" << std::endl;
		else if ( num_ready == 1 )//&& Stop == 1 )
		{
			std::cout << "\nServer: intercepted signal" << std::endl;
		}*/
		
			ConnectClient();
			std::map<int, User*>::iterator it;
			for (it = UserTab.begin(); it != UserTab.end(); ++it)
			{
				int num = it->first;
				User *user = it->second;
				HandleMessage(user, num + 1, client_fds);
			}
	}
}

void	Server::HandleMessage(User *user, int num, std::vector<pollfd> client_fds)
{
	if (client_fds[num].revents & POLLIN)
	{
		char buffer[1024];
		ssize_t bytesRead = recv(client_fds[num].fd, buffer, sizeof(buffer), 0);
		if (bytesRead > 0)
		{
			std::string message(buffer, bytesRead);
			std::cout << user->getUsername() << " command : " << message << std::endl;
			
			size_t end = message.find("\r\n", 0);
			size_t pos = 0;
			while (end != std::string::npos)
			{
				std::string firstCommand = message.substr(pos, end + 2 - pos);
				pos = end + 2;
				FindCommand(user, firstCommand);
				end = message.find("\r\n", pos);
			}
		}
	}
}

void	Server::FindCommand(User *user, std::string command)
{
	size_t found = command.find("\r\n");
	command.erase(found, 2);
	size_t pos1 = command.find(' ');
	size_t pos2 = command.find(' ', pos1 + 1);
	if (command.substr(0, pos1) == "CAP")
	{
		CommandCAP(user);
	}
	if (command.substr(0, pos1) == "PASS")
	{
		CommandPASS(user);
	}
	if (command.substr(0, pos1) == "NICK")
	{
		CommandNICK(user, command.substr(pos1 + 1, pos2));
	}
	if (command.substr(0, pos1) == "USER")
	{
		CommandUSER(user, command.substr(pos1 + 1));
	}
	if (command.substr(0, pos1) == "JOIN")
	{
		CommandJOIN(user, command.substr(pos1 + 1, pos2));
	}
	if (command.substr(0, pos1) == "PRIVMSG")
	{
		CommandPRIVMSG(user, command.substr(pos1 + 1, pos2));
	}
}

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
			channel->Channel::AddUser(user->getUsername());
			user->setChannel(message);
			std::string response4 = ":" + user->getID() + " JOIN " + channel->getName() + "\r\n";	
			send(user->getSocket(), response4.c_str(), response4.size(), 0);
			response4 = ":server 353 " + user->getUsername() + " = " + channel->getName() + " :" + FindChannel(user->getChannel())->getStringUser() + "\r\n";
			send(user->getSocket(), response4.c_str(), response4.size(), 0);
			response4 = ":server 366 " + user->getUsername() + " " + channel->getName() + ":End of /NAMES list.\r\n";
			send(user->getSocket(), response4.c_str(), response4.size(), 0);
			CommandNAMES(user);
			return;
		}
	}
	Channel* newChannel = new Channel(message);
	newChannel->Channel::AddUser("@" + user->getUsername());
	user->setChannel(message);
	ChannelTab[message] = newChannel;
	std::string response4 = ":" + user->getID() + " JOIN " + newChannel->getName() + "\r\n";
	send(user->getSocket(), response4.c_str(), response4.size(), 0);
	response4 = ":server 353 " + user->getUsername() + " = " + newChannel->getName() + " :" + FindChannel(user->getChannel())->getStringUser() + "\r\n";
	send(user->getSocket(), response4.c_str(), response4.size(), 0);
	response4 = ":server 366 " + user->getUsername() + " " + newChannel->getName() + ":End of /NAMES list.\r\n";
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

void	Server::SendMessage(User *user, Channel *channel, std::string mes)
{
	std::string response4 = ":" + user->getUsername() + " PRIVMSG " + channel->getName() + " :" + mes + "\r\n";
	std::cout << response4 << std::endl;
	send(user->getSocket(), response4.c_str(), response4.size(), 0);
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


Server::Server(std::string const &port, std::string const &password) : _password(password)
{
	if (port[0] == '-')
	{
		std::cerr << "Error\nThe port must not be negative." << '\n';
		return ;
	}
	for (char const &c : port)
	{
		if (std::isdigit(c) == false)
		{
			std::cerr << "Error\nPort is not number." << '\n';
			return ;
		}
	}
	if (port.length() > 5 || (this->_port = atoi(port.c_str())) > 65535)
	{
		std::cerr << "Error\nPort should not exceed 65535." << '\n';
		return ;
	}
	if (Server_start() == false)
		return ;
	if (Server_loop() == false)
		return ;
}

Server::~Server() {}
