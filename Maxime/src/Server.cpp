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
	this->SServer.info.sin_addr.s_addr = inet_addr("10.12.2.6");
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
		int num_ready = poll( client_fds.data(), this->numConnection + 1, 1 );
		if ( num_ready == -1 && Stop == 1 )
			std::cout << "\nServer: intercepted signal" << std::endl;
		else if ( num_ready == -1 && Stop == 1 )
			std::cout << "\nServer: Poll error" << std::endl;
		ConnectClient();
		std::map<int, User*>::iterator it;
		for (it = UserTab.begin(); it != UserTab.end(); ++it)
		{
			int num = it->first;
			User *user = it->second;
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
		User *user = new User(this->SClient.fd, this->SClient.fd);
		UserTab[this->numConnection] = user;
		client_fds[this->numConnection + 1].fd = this->SClient.fd;
		client_fds[this->numConnection + 1].events = POLLIN | POLLOUT;
		this->numConnection++;


		
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
			std::cout << user->User::getUsername() << " command : " << message << std::endl;
			ParseCommand(user, message);
		}
	    
	}
	
}

void	Server::ParseCommand(User *user, std::string message)
{
	size_t end = message.find("\r\n", 0);
	size_t pos = 0;
	while (end != std::string::npos)
	{
		std::string firstCommand = message.substr(pos, end + 2 - pos);
		pos = end + 2;
		FindCommand(user, firstCommand);
		end = message.find("\r\n", pos);
	}
	(void)user;
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
		CommandUSER(user);
	}
	if (command.substr(0, pos1) == "JOIN")
	{
		CommandJOIN(user, command.substr(pos1 + 1, pos2));
	}
	if (command.substr(0, pos1) == "PRIVMSG")
	{
		CommandPRIVMSG(user, command.substr(pos1, pos2));
	}
	/*if (command.substr(0, pos1) == "NAMES")
	{
		std::cout << "tesde fout\n";
		CommandNAMES(user);
	}*/
}

void	Server::CommandCAP(User *user)
{
	std::string capabilities = "sasl";
	std::string response = "CAP * LS :" + capabilities + "\r\n";
	send(user->getNum(), response.c_str(), response.size(), 0);
}

void	Server::CommandPASS(User *user)
{
	std::string response2 = ":localhost 001 mlangloi :Welcome to the IRC server\r\n";
	send(user->getNum(), response2.c_str(), response2.size(), 0);
}

void	Server::CommandNICK(User *user, std::string message)
{
	static std::vector<std::string> usernames;
	std::vector<std::string>::iterator it;
	for (it = usernames.begin(); it != usernames.end(); ++it)
	{
		if (message == *it)
			message = message + "1";
		// pas bon : trouver sol pour plusieur fois le meme username
	}
	user->User::setUsername(message);
	//std::cout << "test : " << user.getUsername() << std::endl;
	std::string response3 = ":mlangloi!mlangloi@host mlangloi :mlangloi\r\n";
	send(user->getNum(), response3.c_str(), response3.size(), 0);
}

void	Server::CommandUSER(User *user)
{
	std::string response4 = ":localhost 001 mlangloi :Welcome to the IRC server\r\n";
	std::cout << "test : " << user->getUsername() << std::endl;
	send(user->getNum(), response4.c_str(), response4.size(), 0);
}

void	Server::CommandJOIN(User *user, std::string message)
{
	





	JoinChannel(user, message);
	CommandNAMES(user);
	//std::string response4 = ":server 474 " + user->getUsername() +  message + " :Cannot join channel +b \r\n";

	//send(user->getNum(), response4.c_str(), response4.size(), 0);
}

void	Server::CommandPRIVMSG(User *user, std::string message)
{
	std::cout << "mess : " << message << std::endl;
	SendMessage("#serv", "salut");
	/*if (FindChannel(...) == 1)
	{
		
		//envoyer message au user sur le serv
	}
	else if (FindUser(...) == 1)
	{
		//envoyer messaeg au user
	}*/
	
	(void)user;
}

void	Server::CommandNAMES(User *user)
{
	std::string response4 = ":server 353 " + user->getUsername() + " = " + user->getChannel() + " :" +  user->getUsername() + FindChannel(user->getChannel())->getStringUser() + "\r\n";
	send(user->getNum(), response4.c_str(), response4.size(), 0);
	response4 = ":server 366 " + user->getUsername() + " " + user->getChannel() + " :End of /NAMES list.\r\n";
	send(user->getNum(), response4.c_str(), response4.size(), 0);
	
}



void	Server::SendMessage(std::string channel, std::string message)
{
	std::map<int, User*>::iterator it;
	for (it = UserTab.begin(); it != UserTab.end(); ++it)
	{
		//int num = it->first;
		User *user = it->second;
		if (user->getChannel() == channel)
		{
			// envoyer message
			std::string response3 = ":sender!ldaniel@localhost PRIVMSG #serv :test\r\n";
			send(user->getNum(), response3.c_str(), response3.size(), 0);
		}
	}
	(void)message;
}
