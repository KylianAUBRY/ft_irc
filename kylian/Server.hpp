/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:31:57 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/08 15:46:26 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "include.hpp"

class Server
{
	public :
		Server(std::string const &port, std::string const &password);
		~Server();
		
	private :
		Server();
		int _port;
		const std::string _password;
		
};