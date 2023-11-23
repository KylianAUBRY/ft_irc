/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:28:17 by kylian            #+#    #+#             */
/*   Updated: 2023/11/23 17:17:25 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kylian/include/include.hpp"

int Stop;

void	handle_signal(int signal)
{
	if (signal == SIGINT)
		Stop = 1;
}

void cleanupFunction()
{
	std::cout << "salut" << '\n';
    /*send(sock, "QUIT :leaving\r\n", 16, 0);
    close(sock);*/
}

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
	Stop = 0;
	atexit(cleanupFunction);
	std::signal(SIGINT, handle_signal);
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
	std::string capLs = "CAP LS\r\n";
	std::string nick = "NICK capitalsbot\r\nUSER capitalsbot capitalsbot localhost :capitalsbot\r\n";
    std::string capEnd = "CAP END\r\n";
    send(sock, capLs.c_str(), capLs.size(), 0);
	char buffer[4096];
	int bytes;

	bytes = recv(sock, buffer, sizeof(buffer), 0);
	buffer[bytes] = '\0';
	if (std::strcmp (buffer, "CAP * LS :\r\n") != 0)
	{
		std::cerr << "Error\nsocket binding to failed." << '\n';
		send(sock, "QUIT :leaving\r\n", 16, 0);
		close(sock);
		return 1;
	}
	capLs = "PASS " + std::string (argv[3]) + "\r\n";
	send(sock, capLs.c_str(), capLs.size(), 0);
	bytes = recv(sock, buffer, sizeof(buffer), 0);
	buffer[bytes] = '\0';
	if (std::strcmp(buffer, ":server 464  :password incorrect\r\n") == 0)
	{
		std::cerr << "Error\nPassword incorrect" << '\n';
		send(sock, "QUIT :leaving\r\n", 16, 0);
		close(sock);
		return 1;
	}
	else if (std::strcmp(buffer, ":localhost 001  :Password Correct\r\n") != 0)
	{
		std::cerr << "Error\nError when receiving packet password."	<< '\n';
		send(sock, "QUIT :leaving\r\n", 16, 0);
		close(sock);
		return 1;
	}
	send(sock, nick.c_str(), nick.size(), 0);
	send(sock, capEnd.c_str(), capEnd.size(), 0);
	bytes = recv(sock, buffer, sizeof(buffer), 0);
	buffer[bytes] = '\0';
	if (std::strstr (buffer, ":localhost 001 capitalsbot :Welcome to the IRC server\r\n") == NULL)
	{
		std::cerr << "Error\nsocket binding to failed. Welcome message." << '\n';
		send(sock, "QUIT :leaving\r\n", 16, 0);
		close(sock);
		return 1;
	}
	if (std::strstr(buffer, "CAP * LS :\r\n") == NULL)
	{
		bytes = recv(sock, buffer, sizeof(buffer), 0);
		buffer[bytes] = '\0';
		if (std::strcmp (buffer, "CAP * LS :\r\n") != 0)
		{
			std::cerr << "Error\nsocket binding to failed. CAP LS." << '\n';
			send(sock, "QUIT :leaving\r\n", 16, 0);
			close(sock);
			return 1;
		}
	}
	send(sock, "JOIN #pays\r\n", 13, 0);
	bytes = recv(sock, buffer, sizeof(buffer), 0);
	buffer[bytes] = '\0';
	if (std::strstr(buffer, "JOIN #pays\r\n") == NULL)
	{
		std::cout << buffer << '\n';
		std::cerr << "Error\nimpossible to connect to Chanel : #pays." << '\n';
		send(sock, "QUIT :leaving\r\n", 16, 0);
		close(sock);
		return 1;
	}
	pollfd *fds = new pollfd();
	poll(fds, 1, 1000000);
	while (Stop == 0)
	{
		if (fds->revents & POLLIN)
			break ;
		bytes = recv(sock, buffer, sizeof(buffer), 0);
		buffer[bytes] = '\0';
		std::cout << buffer << '\n';
	}
	delete(fds);
	send(sock, "QUIT :leaving\r\n", 16, 0);
    close(sock);
	return 0;
}