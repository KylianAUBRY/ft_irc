/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:01:31 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/15 19:35:05 by kyaubry          ###   ########.fr       */
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
		void AddUser(User *user);
		void DelUser(User *user);
		std::string getStringUser();
		void SendMsg(User *user, std::string message);
		bool IsHere(User *user);
	private :
		const std::string _name;
		std::vector<User*> UserBook;
};
