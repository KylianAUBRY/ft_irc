/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:42:01 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/14 16:45:04 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/User.hpp"

User::User(int socket) : _socket(socket)
{
	_username = "";
}

User::~User()
{
	close(this->_socket);
}

std::string User::getUsername(void)
{
	return (_username);
}

void User::setUsername(std::string username)
{
	this->_username = username;
}
