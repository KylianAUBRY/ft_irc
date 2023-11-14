/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:41:54 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/14 16:45:12 by kyaubry          ###   ########.fr       */
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
		void setUsername(std::string username);
	private :
		const int _socket;
		std::string _username;
};