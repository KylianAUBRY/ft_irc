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
	this->SServer.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->SServer.fd == -1)
	{
		perror("socket");
		return 1;
	}
	this->SServer.info.sin_addr.s_addr = inet_addr("127.0.0.1");
	this->SServer.info.sin_family = AF_INET;
	this->SServer.info.sin_port = htons(30000);
	if (bind(this->SServer.fd, (const struct sockaddr *)&this->SServer.info, sizeof(this->SServer.info)) == -1)
	{
		perror("bind");
		close(this->SServer.fd);
		return 1;
	}
	printf("bind : %d\n", this->SServer.fd);
	if (listen(this->SServer.fd, 1) == -1)
	{
		perror("listen");
		close(this->SServer.fd);
		return 1;
	}
	printf("listen\n");
	std::vector<pollfd> &client_fds = *poll_fds;
	client_fds[0].fd = this->SServer.fd;
	client_fds[0].events = POLLIN;
	numConnection = 0;
	while (Stop == 0)
	{
		std::vector<pollfd> &client_fds = *poll_fds;

		int num_ready = poll( client_fds.data(), this->numConnection + 1, -1 );
		if ( num_ready == -1 && Stop == 1 )
			std::cout << "\nServer: intercepted signal" << std::endl;
		else if ( num_ready == -1 && Stop == 1 )
			std::cout << "\nServer: Poll error" << std::endl;
		ConnectClient();
		
		
		
		
		
		
		for (int i = 1; i <= this->numConnection; i++)
    {
        if (client_fds[i].revents & POLLIN)
        {
            char buffer[1024];
            ssize_t bytesRead = recv(client_fds[i].fd, buffer, sizeof(buffer), 0);

            if (bytesRead > 0)
            {
                std::string message(buffer, bytesRead);

                // Votre logique de traitement des commandes ici
                if (message.find("/mycustomcommand") == 0)
                {
                    // Interceptez la commande /mycustomcommand
                    // Effectuez les actions associées à cette commande
                    std::string parameters = message.substr(15); // Pour extraire les paramètres de la commande
                    // Faites ce que vous devez faire avec les paramètres
                    std::cout << "Commande personnalisée interceptée : " << parameters << std::endl;
                }
            }
        }
    }
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
		
	close(this->SServer.fd);
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
		socklen_t csize = sizeof(this->SClient.info);
		this->SClient.fd = accept(this->SServer.fd, (struct sockaddr *)&this->SClient.info, &csize);
		if (this->SClient.fd == -1)
		{
			perror("accept");
			close(this->SServer.fd);
			return ;
		}
		std::cout << "New client connected: " << this->SClient.fd << std::endl;
		this->numConnection++;
		new User(this->SClient.fd);
	}
			
}
