/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:40:59 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/21 13:02:16 by kyaubry          ###   ########.fr       */
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
	close(this->SServer.fd);
	delete poll_fds;
	return true;
}

void	Server::HandleMessage(User *user, int num, std::vector<pollfd> client_fds)
{
	std::string message2;
	if (client_fds[num].revents & POLLIN)
	{
		while (1)
		{
			char buffer[255];
			ssize_t bytesRead = recv(client_fds[num].fd, buffer, sizeof(buffer), 0);
			if (bytesRead > 0)
			{
				std::string message1(buffer, bytesRead);
				message2 += message1;
				size_t end = message2.find("\r\n", 0);
				size_t pos = 0;
				if (end != std::string::npos)
				{
					//std::cout << user->getUsername() << " command recu entierement : " << message2;
					while (end != std::string::npos)
					{
						std::string firstCommand = message2.substr(pos, end + 2 - pos);
						pos = end + 2;
						FindCommand(user, firstCommand);
						end = message2.find("\r\n", pos);
					}
					message2 = "";
					return ;
				}
				else
				{
					//std::cout << "non recus entierement "<< message2 << '\n';
					continue;
				}
			}
		}
	}
}

void	Server::FindCommand(User *user, std::string command)
{
	static int passOK = 1;
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
		passOK = CommandPASS(user, command.substr(pos1 + 1));
	}
	if (command.substr(0, pos1) == "NICK")
	{
		CommandNICK(user, command.substr(pos1 + 1, pos2));
	}
	if (command.substr(0, pos1) == "USER")
	{
		CommandUSER(user, command.substr(pos1 + 1), passOK);
	}
	if (command.substr(0, pos1) == "JOIN")
	{
		CommandJOIN(user, command.substr(pos1 + 1));
	}
	if (command.substr(0, pos1) == "PRIVMSG")
	{
		CommandPRIVMSG(user, command.substr(pos1 + 1));
	}
	if (command.substr(0, pos1) == "PART")
	{
		CommandPART(user, command.substr(pos1 + 1, pos2));
	}
	if (command.substr(0, pos1) == "MODE")
	{
		CommandMODE(user, command.substr(pos1 + 1));
	}
	if (command.substr(0, pos1) == "TOPIC")
	{
		CommandTOPIC(user, command.substr(pos1 + 1));
	}
	if (command.substr(0, pos1) == "INVITE")
	{
		CommandINVITE(user, command.substr(pos1 + 1));
	}
	if (command.substr(0, pos1) == "KICK")
	{
		CommandKICK(user, command.substr(pos1 + 1));
	}
	if (command.substr(0, pos1) == "QUIT")
	{
		CommandQUIT(user, command.substr(pos1 + 1));
	}
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

