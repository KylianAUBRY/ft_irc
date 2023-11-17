/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:23:04 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/17 15:28:11 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void 	Server::ModeK(User *user, Channel *channel, std::string message, int i)
{
	
	
	
	if (channel->getMode('k') == false && i == 0)
	{
		
		std::cout << "message = "<< message << '\n';
		std::cout << "mode = " << i << '\n';
		
		channel->SetPassword(message);
		channel->SetMode('k', true);
		std::string response = user->getID() + " MODE " + channel->getName() + " +k " + message + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		

	}
}

void 	Server::ModeI(User *user, Channel *channel, int i)
{
	
}
