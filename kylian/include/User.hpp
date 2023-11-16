/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:41:54 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/15 12:11:19 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "include.hpp"

class User
{
	public :
		User(int socket);
		~User();
		std::string getUsername(void);
		std::string getNickname(void);
		std::string getChannel(void);
		std::string getHostname(void);
		int getSocket(void);
		bool getGetNick(void);
		std::string getID(void);
		void setUsername(std::string username);
		void setNickname(std::string nickname);
		void setChannel(std::string channel);
		void setHostname(std::string hostname);
		void setGetNick();
	private :
		const int _socket;
		std::string _username;
		std::string _nickname;
		std::string _channel;
		std::string _hostname;
		bool _getNick;
};
