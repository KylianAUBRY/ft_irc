/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:41:54 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/24 15:48:43 by kyaubry          ###   ########.fr       */
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
		int getisDown(void);
		bool getGetNick(void);
		std::string getID(void);
		std::string getbuffCommand(void);
		std::string getIp(void);
		void setisDown(int down);
		void setUsername(std::string username);
		void setNickname(std::string nickname);
		void setChannel(std::string channel);
		void setHostname(std::string hostname);
		void setGetNick();
		void setbuffCommand(std::string command);
		void joinbuffCommand(std::string command);
		void incrementisDown();
		void setIp(std::string ip);
	private :
		int _isDown;
		const int _socket;
		std::string _username;
		std::string _nickname;
		std::string _channel;
		std::string _hostname;
		std::string _buffCommand;
		std::string _ip;
		bool _getNick;
};
