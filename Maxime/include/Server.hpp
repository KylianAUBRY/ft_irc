/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:21:44 by mlangloi          #+#    #+#             */
/*   Updated: 2023/10/25 17:21:45 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<iostream>
#include<stack>
#include<vector>
#include <map>
#include <csignal>
#include <poll.h>
#include <iterator>
#include"../include/User.hpp"
#include"../include/Channel.hpp"

class User;

static bool Stop = 0;

struct s_socket
{
	int fd;
	struct sockaddr_in info; 
};

class Server
{
	public:
		Server();
		~Server();
		int	InitializeServ();
		static void	handle_signal(int signal);
		void	ConnectClient();
		void	Message();
		std::map<int, User*> UserTab;
	
	private:
		int numConnection;
		std::vector<pollfd> * poll_fds;
		s_socket SClient;
		s_socket SServer;
		
		

};

void	SendMessage(std::string channel, std::string message);

#endif
