/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:40:59 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/24 16:01:27 by kyaubry          ###   ########.fr       */
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
		//std::cout << "New client connected: " << this->SClient.fd << std::endl;
		try
		{
			User *user = new User(this->SClient.fd);
			char clientIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(this->SClient.info.sin_addr), clientIP, INET_ADDRSTRLEN);
			user->setIp(clientIP);
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
	std::signal(SIGINT, Server::handle_signal);
	while (Stop == 0)
	{
		int num_ready = poll(client_fds.data(), this->numConnection + 1, 1000000);
		ConnectClient();
		std::map<int, User*> UserTab2 = UserTab;
		std::map<int, User*>::iterator it;
		for (it = UserTab2.begin(); it != UserTab2.end(); ++it)
		{
			int num = it->first;
			User *user = it->second;
			HandleMessage(user, num + 1, client_fds);
		}
	}
	if (UserTab.size() != 0)
	{
		std::map<int, User*> UserTab2 = UserTab;
		std::map<int, User*>::iterator it;
		for (it = UserTab2.begin(); it != UserTab2.end(); ++it)
		{
			int num = it->first;
			User *user = it->second;
			CommandQUIT(user, ":Stop Server");
		}
	}
	if (ChannelTab.size() != 0)
	{\
		std::map<std::string, Channel*> ChannelTab2 = ChannelTab;
		std::map<std::string, Channel*>::iterator itt;
		for (itt = ChannelTab2.begin(); itt != ChannelTab2.end(); ++itt)
		{
			std::string name = itt->first;
			Channel *channel = itt->second;
			delete channel;
			ChannelTab2.erase(itt);
		}
	}
	close(this->SServer.fd);
	delete poll_fds;
	return true;
}

void	Server::timeOut(User *user)
{
	std::string chan = user->getChannel();
	if (chan != "")
	{
		std::map<std::string, Channel*>::iterator it;
		for (it = ChannelTab.begin(); it != ChannelTab.end(); ++it)
		{
			std::string name = it->first;
			Channel* channel = it->second;
			if (chan == name)
			{
				std::string response1 = user->getID() + " QUIT " + " :" + "time out" + "\r\n";
				channel->SendMsg(user, response1);
				channel->DelUser(user);
				if (channel->isEmpty() == true)
				{
					delete channel;
					ChannelTab.erase(it);
				}
				std::map<int, User*>::iterator itt;
				for (itt = UserTab.begin(); itt != UserTab.end(); ++itt)
				{
					User* userT = itt->second;
					if (user->getNickname() == userT->getNickname())
					{	
						delete user;
						user = NULL;
						UserTab.erase(itt);
						this->numConnection --;
						return;
					}
				}
			}
		}
	}
	else
	{
		std::map<int, User*>::iterator itt;
		for (itt = UserTab.begin(); itt != UserTab.end(); ++itt)
		{
			User* userT = itt->second;
			if (user->getNickname() == userT->getNickname())
			{	
				delete user;
				user = NULL;
				UserTab.erase(itt);
				this->numConnection --;
				return;
			}
		}
	}
}

void	Server::HandleMessage(User *user, int num, std::vector<pollfd> client_fds)
{
	if (client_fds[num].revents & POLLIN)
	{
		char buffer[255];
		ssize_t bytesRead = recv(client_fds[num].fd, buffer, sizeof(buffer) - 1, 0);
		buffer[bytesRead] = '\0';
		if (bytesRead == 0)
		{
			user->incrementisDown();
			if (user->getisDown() >= 100)
				return timeOut(user);
		}
		else
			user->setisDown(0);
		if (bytesRead > 0)
		{
			std::string message1(buffer, bytesRead +1);
			user->joinbuffCommand(message1);
			size_t end;
			if (user->getbuffCommand() == "")
				end = std::string::npos;
			else
				end = user->getbuffCommand().find("\r\n", 0);
			size_t pos = 0;
			if (end != std::string::npos)
			{
				//std::cout << user->getUsername() << " command recu entierement : " << user->getbuffCommand();
				while (end != std::string::npos)
				{
					std::string firstCommand = user->getbuffCommand().substr(pos, end + 2 - pos);
					pos = end + 2;
					if (FindCommand(user, firstCommand) == 1)
						return ;
					end = user->getbuffCommand().find("\r\n", pos);
				}
				user->setbuffCommand("");
				return ;
			}
			else
			{
				//std::cout << "non recu entierement "<< user->getbuffCommand() << '\n';
			}
		}
	}
}

int		Server::FindCommand(User *user, std::string command)
{
	static int passOK = 1;
	size_t found = command.find("\r\n");
	command.erase(found, 2);
	size_t pos1 = command.find(' ');
	size_t pos2 = command.find(' ', pos1 + 1);
	if (command.substr(0, pos1) == "CAP")
		CommandCAP(user);
	else if (command.substr(0, pos1) == "PASS")
		passOK = CommandPASS(user, command.substr(pos1 + 1));
	else if (command.substr(0, pos1) == "NICK")
		CommandNICK(user, command.substr(pos1 + 1, pos2));
	else if (command.substr(0, pos1) == "USER")
		CommandUSER(user, command.substr(pos1 + 1), passOK);
	else if (command.substr(0, pos1) == "JOIN")
		CommandJOIN(user, command.substr(pos1 + 1));
	else if (command.substr(0, pos1) == "PRIVMSG")
		CommandPRIVMSG(user, command.substr(pos1 + 1));
	else if (command.substr(0, pos1) == "PART")
		CommandPART(user, command.substr(pos1 + 1, pos2));
	else if (command.substr(0, pos1) == "MODE")
		CommandMODE(user, command.substr(pos1 + 1));
	else if (command.substr(0, pos1) == "TOPIC")
		CommandTOPIC(user, command.substr(pos1 + 1));
	else if (command.substr(0, pos1) == "INVITE")
		CommandINVITE(user, command.substr(pos1 + 1));
	else if (command.substr(0, pos1) == "KICK")
		CommandKICK(user, command.substr(pos1 + 1));
	else if (command.substr(0, pos1) == "PING")
		CommandPING(user, command.substr(pos1 + 1));
	else if (command.substr(0, pos1) == "QUIT")
	{
		CommandQUIT(user, command.substr(pos1 + 1));
		return 1;
	}
	return 0;
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

void	Server::handle_signal(int signal)
{
	if (signal == SIGINT)
		Stop = 1;
}

Server::~Server() {}

