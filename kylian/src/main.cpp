/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:59:17 by kyaubry           #+#    #+#             */
/*   Updated: 2023/11/14 15:02:40 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "./ircserv <port> <password>" << '\n';
		return 1;
	}
	Server serv(argv[1], argv[2]);
}
