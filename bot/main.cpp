/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:28:17 by kylian            #+#    #+#             */
/*   Updated: 2023/11/23 13:51:55 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.hpp"

int ft_chr_port(std::string port)
{
	if (port[0] == '-')
	{
		std::cerr << "Error\nThe port must not be negative." << '\n';
		return -1;
	}
	for (char const &c : port)
	{
		if (std::isdigit(c) == false)
		{
			std::cerr << "Error\nPort is not number." << '\n';
			return -1;
		}
	}
	if (port.length() > 5 || atoi(port.c_str()) > 65535)
	{
		std::cerr << "Error\nPort should not exceed 65535." << '\n';
		return -1;
	}
	return atoi(port.c_str());
}

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "./botirc <address> <port> <password>" << '\n';
		return 1;	
	}
	int port = ft_chr_port(argv[2]);
	if (port == -1)
		return 1;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		std::cerr << "Error\nSocket creation failed." << '\n';
		return 1;
	}
	struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0)
	{
    	std::cerr << "Error\nInvalide ip." << '\n';
        close(sock);
        return 1;
    }
    // Copie de l'adresse IP résolue dans la structure sockaddr_in
    struct sockaddr_in serverAddress;
    memcpy(&serverAddress.sin_addr, &((struct sockaddr_in*)result->ai_addr)->sin_addr, sizeof(struct in_addr));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    freeaddrinfo(result);
	if (connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
	{
        std::cerr << "Error\nConnection to server failed." << '\n';
        close(sock);
        return -1;
    }
	std::string capLs = "CAP LS\nPASS " + std::string (argv[3]) + "\r\n";
	std::string nick = "NICK capitalsBote\nUSER capitalsBote capitalsBote localhost :capitalsBote\r\n";
    std::string capEnd = "CAP END\r\n";
    send(sock, capLs.c_str(), capLs.size(), 0);
	char buffer[4096];
	int bytes;

	bytes = recv(sock, buffer, sizeof(buffer), 0);
	buffer[bytes] = '\0';
	if (std::strcmp (buffer, "CAP * LS :\r\n") != 0)
	{
		std::cerr << "Error\nsocket binding to failed." << '\n';
		close(sock); //message de deconnection a renvoyer au server.
		return 1;
	}
	bytes = recv(sock, buffer, sizeof(buffer), 0);
	buffer[bytes] = '\0';
	if (std::strcmp(buffer, ))
	
	bytes = recv(sock, buffer, sizeof(buffer), 0);
	buffer[bytes] = '\0';
	/*if (buffer != "CAP * LS :sasl\r\n")
	{
		std::cerr << "Error\nsocket binding to failed." << '\n';
		close(sock);
		return 1;
	}*/
	std::cout << buffer << '\n';
	return  0; 
	send(sock, nick.c_str(), nick.size(), 0);
    send(sock, capEnd.c_str(), capEnd.size(), 0);
	//send(sock, capLs.c_str(), capLs.size(), 0);

    // Reste du code (envoi de messages, lecture des messages, etc.)
	while (1)
		;
    // Fermeture du socket
    close(sock);
}

