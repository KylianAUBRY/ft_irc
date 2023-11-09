/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:54:33 by mlangloi          #+#    #+#             */
/*   Updated: 2023/10/27 17:54:33 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"User.hpp"

User::User()
{
}

User::User(int socket) : username("user"), socket(socket)
{
	std::cout << "aaaaaaaaaa" << this->username << this->socket << std::endl;
}

User::~User()
{
}

int User::getSocket()
{
	return (this->socket);
}

void	HandleMessage(User user, int num, std::vector<pollfd> client_fds)
{
	if (client_fds[num].revents & POLLIN)
	{
		char buffer[1024];
		ssize_t bytesRead = recv(client_fds[num].fd, buffer, sizeof(buffer), 0);

		if (bytesRead > 0)
		{
			std::string message(buffer, bytesRead);
			ParseCommand(user, message);
		}
	    
	}
	
}

void	ParseCommand(User user, std::string message)
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

void	FindCommand(User user, std::string command)
{
	size_t pos1 = command.find(' ');
	size_t pos2 = command.find(' ', pos1 + 1);
	if (command.substr(0, pos1) == "CAP")
	{
		std::cout << "le cap est : " << command.substr(pos1 + 1, pos2 - pos1 - 1) << std::endl;
		
	}
	if (command.substr(0, pos1) == "PASS")
	std::cout << "le mot de passe est : " << command.substr(pos1 + 1, pos2 - pos1 - 1) << std::endl;
	if (command.substr(0, pos1) == "NICK")
	std::cout << "le nom est : " << command.substr(pos1 + 1, pos2 - pos1 - 1) << std::endl;
	if (command.substr(0, pos1) == "USER")
	std::cout << "l'utilisateur est : " << command.substr(pos1 + 1, pos2 - pos1 - 1) << std::endl;
	(void)user;
}

void	CommandCAP(User user)
{
	std::string capabilities = "sasl";
	std::string response = "CAP * LS :" + capabilities + "\r\n";
	send(this->SClient.fd, response.c_str(), response.size(), 0);
}

void	CommandPASS(User user)
{
	std::string response2 = ":localhost 001 mlangloi :Welcome to the IRC server\r\n";
	send(this->SClient.fd, response2.c_str(), response2.size(), 0);
}

void	CommandNICK(User user)
{
	std::string response3 = ":mlangloi!mlangloi@host mlangloi :mlangloi\r\n";
		send(this->SClient.fd, response3.c_str(), response3.size(), 0);
}

void	CommandUSER(User user)
{
	std::string response4 = ":localhost 001 mlangloi :Welcome to the IRC server\r\n";
		send(this->SClient.fd, response4.c_str(), response4.size(), 0);
}
