/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:54:44 by mlangloi          #+#    #+#             */
/*   Updated: 2023/10/27 17:54:45 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include"../include/Server.hpp"

class User
{
	public:
		User();
		User(int socket, int num);
		~User();
		int getSocket();
		int getNum();
		void setUsername(std::string name);
		void setChannel(std::string newChannel);
		std::string getUsername();
		std::string getChannel();
	
		
	
	private:
		std::string username;
		int socket;
		int num;
		std::string channel;
		
		
		

};



#endif
