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
	std::cout << "message = "<< message << '\n';
	std::cout << "mode = " << i << '\n';
}

void 	Server::ModeI(User *user, Channel *channel, int i)
{
	
}