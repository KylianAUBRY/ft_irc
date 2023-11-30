# ft_irc

ft_irc est un projet de la partie obligatoire du cursus. Il est uniquement réalisé en C++ et l'objectif principal était de recréer un serveur IRC.



## Le protocole IRC

Le protocole IRC est un protocole reposant sur de multiples échanges de textes continus, il contient 2 types de connexions : la connexion serveur/serveur qu'on ne prend pas en compte sur ce projet car elle est utile sur les grands reseaux, et la connexion serveur/client (celle qui nous interesse ici).


## Fonctionnement

Le programme prendra comme argument le port souhaite puis le mot de passe, à l'execution il creera un serveur IRC capable de prendre en charge les connexions d'un client (pour notre projet, nous avons choisi IRSSI) et executer les commandes envoye par celui ci. Pour communique ravec le client nous utilisons des textez precis (RPL), sous la forme suivante :

`":server 001 nick :Welcome to the IRC server\r\n"`

`":nick!user@host JOIN channel\r\n"`

![https://im3.ezgif.com/tmp/ezgif-3-7f02b5dd9d.mp4](https://im3.ezgif.com/tmp/ezgif-3-615cbe5421.gif)

## Commandes

Voici toutes les commandes que nous avons implemante :

|Commande |Description|
|---|---|
|CAP| negocier les capacites entre le serveur et le client|
|PASS| gerer le mot de passe du serveur|
|NICK| changer de nom sur le serveur|
|USER| s'identifier et acceder au serveur|
|JOIN| rejoindre un cannal|
|PRIVMSG| envoyer un message (canal ou prive)|
|PART| quiter un canal|
|MODE| changer le mode d'un canal|
|TOPIC| ajouter/changer le topic d'un canal|
|INVITE| inviter quelqu'un dans le canal|
|KICK| exclure quelqu'un d'un canal|
|PING| maintenir la connexion serveur/client|
|QUIT| quitter le serveur|

et les differents mode de canal :

|Mode |Description|
|---|---|
|i| mettre en invite-only|
|t| bloquer le changement de topic|
|k| mettre un mot de passe|
|o| mettre un utilisateur operateur|
|l| mettre un nombre limite d'utilisateur|


## Bonus

#### Transfert de fichier

Le transfert de fichier se gere comme un message prive normal sur IRSSI, il faut juste s'assurer d'avoir les adresses IP de chaque utilisateurs

#### Bot

Le bot est un client que l'on connecte sur notre serveur puis il rejoint le canal "pays" et il comptabilise le nombre de capitale du monde que vous ecrivez, exemple :

![https://im3.ezgif.com/tmp/ezgif-3-528551ecb2.gif](https://im3.ezgif.com/tmp/ezgif-3-95a2b5d36e.gif)
