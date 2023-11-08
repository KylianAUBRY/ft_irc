/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:21:18 by mlangloi          #+#    #+#             */
/*   Updated: 2023/10/25 17:21:27 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Server.hpp"

Server::Server()
{
}

Server::~Server()
{
	delete poll_fds;
}

int Server::InitializeServ()
{
	std::signal(SIGINT, Server::handle_signal);
	poll_fds = new std::vector<pollfd>( SOMAXCONN + 1 );
	this->socketServer = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketServer == -1)
	{
		perror("socket");
		return 1;
	}
	struct sockaddr_in addrServer;
	addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(30000);
	if (bind(this->socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer)) == -1)
	{
		perror("bind");
		close(this->socketServer);
		return 1;
	}
	printf("bind : %d\n", this->socketServer);
	if (listen(this->socketServer, 1) == -1)
	{
		perror("listen");
		close(this->socketServer);
		return 1;
	}
	printf("listen\n");
	std::vector<pollfd> &client_fds = *poll_fds;
	client_fds[0].fd = this->socketServer;
	client_fds[0].events = POLLIN;
	numConnection = 0;
	while (Stop == 0)
	{
		std::vector<pollfd> &client_fds = *poll_fds;

		int num_ready = poll( client_fds.data(), this->numConnection + 1, -1 );
		if ( num_ready == -1 && Stop == 1 )
			std::cout << "Server: intercepted signal" << std::endl;
		else if ( num_ready == -1 && Stop == 1 )
			std::cout << "Server: Poll error" << std::endl;
		ConnectClient();
		
	}
		
		////////BOUCLE PRINCIPALE
		//readMessage();
		
		

		//close(socketClient);
	/*while(!socketClient.empty())
	{
		int element = socketClient.top();
		socketClient.pop();
		std::cout << element << std::endl;
       	close(element);
	}*/
	close(this->socketServer);
	std::cout << "close" << std::endl;
	
	return 0;
}

int Server::readMessage()
{
	std::cout << "test" << std::endl;
	while (1);
	
}

void	Server::handle_signal(int signal)
{
	if (signal == SIGINT)
		Stop = 1;
}

void	Server::ConnectClient()
{
	std::vector<pollfd> &client_fds = *poll_fds;
	if (client_fds[0].revents & POLLIN)
	{
		struct sockaddr_in addrClient;
		socklen_t csize = sizeof(addrClient);
		this->socketClient.push(accept(this->socketServer, (struct sockaddr *)&addrClient, &csize));
		if (this->socketClient.top() == -1)
		{
			perror("accept");
			close(this->socketServer);
			return ;
		}
		std::cout << "New client connected: " << this->socketClient.top() << std::endl;
		this->numConnection++;
		new User(this->socketClient.top());
	}
			
}
