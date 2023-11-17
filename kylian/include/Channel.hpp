/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:01:31 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/16 16:39:13 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "include.hpp"
# include "User.hpp"

class Channel
{
	public :
		Channel(std::string name);
		~Channel();
		std::string getName(void);
		void AddUser(User *user, std::string mdp, int super);
		void DelUser(User *user);
		std::string getStringUser(std::string name);
		void SendMsg(User *user, std::string message);
		bool IsHere(User *user);
		void SetPassword(std::string password);
		std::string getPassword(void);
		bool isEmpty();
	private :
		std::string _password;
		const std::string _name;
		std::map<User*, int> UserBook;
};
