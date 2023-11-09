/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:40:59 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/09 17:23:32 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool Server::Server_start()
{
	int opt = 1;
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
	return true;
}

void	Server::ConnectClient()
{
	if (client_fds[0].revents & POLLIN)
	{
		std::cout << "w" << '\n';
	}
}

bool Server::Server_loop()
{
	this->client_fds = new pollfd;
	client_fds[0].fd = this->SServer.fd;
	client_fds[0].events = POLLIN; 
	int numConnection = 0;
	while (1)
	{
		int num_ready = poll(client_fds, numConnection + 1, 1000000); // a ajuster le time 
		if ( num_ready == 1 )//&& Stop == 1 )
			std::cout << "\nServer: intercepted signal" << std::endl;
		else if ( num_ready < 0 )//&& Stop == 1 )
			std::cout << "\nServer: Poll error" << std::endl;
		else
		{
			//std::cout << "eee" << '\n';
		}
		
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

Server::~Server() {}