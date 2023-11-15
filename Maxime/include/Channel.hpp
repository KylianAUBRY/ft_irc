/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:01:31 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/14 15:03:44 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "include.hpp"

class Channel
{
	public :
		Channel(std::string name);
		~Channel();
		std::string getName(void);
		void AddUser(std::string user);
		std::string getStringUser();
		void DelUser(std::string user);
	private :
		const std::string _name;
		std::vector<std::string> UserBook;
};
