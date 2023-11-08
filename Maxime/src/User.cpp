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

void	HandleMessage(User user, std::vector<pollfd> client_fds)
{
	if (client_fds[user.getSocket()].revents & POLLIN)
	{
		char buffer[1024];
		ssize_t bytesRead = recv(client_fds[user.getSocket()].fd, buffer, sizeof(buffer), 0);

		if (bytesRead > 0)
		{
			
			std::string message(buffer, bytesRead);
			std::cout << "Commande interceptée : " << message << std::endl;
		}
	    }
	
}
