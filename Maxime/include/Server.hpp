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
		void	SendMessage(std::string channel, std::string message);
		
		
		
		void	HandleMessage(User *user, int num, std::vector<pollfd> client_fds);
		void	ParseCommand(User *user, std::string message);
		void	FindCommand(User *user, std::string command);
		void	CommandCAP(User *user);
		void	CommandPASS(User *user);
		void	CommandNICK(User *user, std::string message);
		void	CommandUSER(User *user);
		void	CommandJOIN(User *user, std::string message);
		void	CommandPRIVMSG(User *user, std::string message);
		void	CommandNAMES(User *user);
	
	private:
		int numConnection;
		std::vector<pollfd> * poll_fds;
		s_socket SClient;
		s_socket SServer;
		
		

};


#endif
