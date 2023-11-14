/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:31:57 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/14 16:48:25 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "include.hpp"
# include "Channel.hpp"
# include "User.hpp"

struct s_socket
{
	int fd;
	struct sockaddr_in info; 
};

class Server
{
	public :
		Server(std::string const &port, std::string const &password);
		~Server();
		
	private :
		Server();
		int _port;
		const std::string _password;
		s_socket SClient;
		s_socket SServer;

		std::vector<pollfd> * poll_fds;
		int numConnection;

		std::map<int, User*> UserTab;
		std::map<std::string, Channel*> ChannelTab;
		
		void	HandleMessage(User *user, int num, std::vector<pollfd> client_fds);
		void	FindCommand(User *user, std::string command);
		void	ConnectClient();
		bool Server_start();
		bool Server_loop();
		void	CommandCAP(User *user);
		void	CommandPASS(User *user);
		void	CommandNICK(User *user, std::string message);
		void	CommandJOIN(User *user, std::string message);
		void	CommandUSER(User *user);
		void	CommandNAMES(User *user);
		Channel	*FindChannel(std::string search);
};
