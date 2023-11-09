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
	int opt = 1;
	std::signal(SIGINT, Server::handle_signal);
	poll_fds = new std::vector<pollfd>( SOMAXCONN + 1 );
	this->SServer.fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(this->SServer.fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
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
		std::map<int, User>::iterator it;
		for (it = UserTab.begin(); it != UserTab.end(); ++it)
		{
			int num = it->first;
			User user = it->second;
			HandleMessage(user, num + 1, client_fds);
		}


	}
		
	close(this->SServer.fd);
	for (int i = 1; i <= this->numConnection + 2; i++)
	{
	
	if (client_fds[i].revents)
	{
		close(client_fds[i].fd);
	}
	}
	std::cout << "close" << std::endl;
	
	return 0;
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
		User user(this->SClient.fd, this->SClient.fd);
		UserTab[this->numConnection] = user;
		client_fds[this->numConnection + 1].fd = this->SClient.fd;
		client_fds[this->numConnection + 1].events = POLLIN | POLLOUT;
		this->numConnection++;
		
		/*// Réponse à la commande CAP LS (envoyer la liste des capacités)
		std::string capabilities = "sasl";  // Liste des capacités prises en charge par le serveur
		std::cout << "tttttttttttttttttest " << this->SClient.fd << std::endl;
		std::string response = "CAP * LS :" + capabilities + "\r\n";
		send(this->SClient.fd, response.c_str(), response.size(), 0);
		*/
		/*
		// Vérifier le mot de passe du client
		
		    std::string response2 = ":localhost 001 mlangloi :Welcome to the IRC server\r\n";
		    send(this->SClient.fd, response2.c_str(), response2.size(), 0);
		
		
		// Accepter le changement de pseudonyme
		std::string response3 = ":mlangloi!mlangloi@host mlangloi :mlangloi\r\n";
		send(this->SClient.fd, response3.c_str(), response3.size(), 0);


	// Accepter les informations de l'utilisateur
		std::string response4 = ":localhost 001 mlangloi :Welcome to the IRC server\r\n";
		send(this->SClient.fd, response4.c_str(), response4.size(), 0);
*/


		
	}
			
}


