/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:31:57 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/09 17:21:40 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "include.hpp"

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

		pollfd *client_fds;
		
		void	ConnectClient();
		bool Server_start();
		bool Server_loop();
};