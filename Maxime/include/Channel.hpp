/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:10:09 by mlangloi          #+#    #+#             */
/*   Updated: 2023/11/09 19:10:10 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include"../include/Server.hpp"
#include"../include/User.hpp"

class User;

class Channel
{
	public:
		Channel();
		Channel(std::string name);
		~Channel();
		std::string getName();
		static std::map<std::string, Channel> ChannelBook;
		void AddUser(User user);
		
	
	private:
		std::string name;
		std::vector<User> UserBook;
		
		

};

int FindChannel(std::string search);
void JoinChannel(User user, std::string search);

#endif
