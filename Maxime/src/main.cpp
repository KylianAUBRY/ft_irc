/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:04:59 by mlangloi          #+#    #+#             */
/*   Updated: 2023/10/24 14:05:01 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Server.hpp"






int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return (1);
	}
	
	
	
	
	
	(void)av;
	int err;
	Server Serv;
	err = Serv.InitializeServ();
	return 0;
	
}


/*
int main() {

    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServer == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in addrServer;
    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(30000);

    if (bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer)) == -1) {
        perror("bind");
        close(socketServer);
        return 1;
    }

    printf("bind : %d\n", socketServer);

    if (listen(socketServer, 1) == -1) {
        perror("listen");
        close(socketServer);
        return 1;
    }

    printf("listen\n");

    struct sockaddr_in addrClient;
    socklen_t csize = sizeof(addrClient);
    int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);

    if (socketClient == -1) {
        perror("accept");
        close(socketServer);
        return 1;
    }

    printf("accept\n");
    printf("client: %d\n", socketClient);


	char buffer[1024];
    while (1) {
        // Lire des données depuis le client.
        ssize_t bytesRead = recv(socketClient, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            perror("recv");
            break;
        }
	 //send(socketClient, "Hello, client!", 14, 0);
	 printf("%s\n", buffer);
        // Traiter les données reçues (par exemple, afficher ou répondre au client).

        // Vous pouvez également envoyer des données au client.
       
    }
    // Vous pouvez maintenant gérer la communication avec le client ici.

    close(socketClient);
    close(socketServer);
    printf("close\n");
    return 0;
}*/

