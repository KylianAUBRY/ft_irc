/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:23:04 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/17 17:55:23 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void 	Server::ModeK(User *user, Channel *channel, std::string message, int i)
{
	std::cout << "message = "<< message << '\n';
	std::cout << "mode = " << i << '\n';
}

void 	Server::ModeI(User *user, Channel *channel, int i)
{
	
}

void 	Server::ModeT(User *user, Channel *channel, int i)
{
	if (channel->getMode('t') == false && i == 0)
	{
		channel->SetMode('t', true);
		std::string response = user->getID() + " MODE " + channel->getName() + " +t " + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user ,response);
		
	}else if (channel->getMode('t') == true && i == 1)
	{
		channel->SetMode('t', false);
		std::string response = user->getID() + " MODE " + channel->getName() + " -t " + "\r\n";
		send(user->getSocket(), response.c_str(), response.size(), 0);
		channel->SendMsg(user ,response);
	}
}