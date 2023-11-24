/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:28:17 by kylian            #+#    #+#             */
/*   Updated: 2023/11/24 03:42:34 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kylian/include/include.hpp"

int Stop;

void	handle_signal(int signal)
{
	if (signal == SIGINT)
		Stop = 1;
}

void cleanupFunction()
{
//	std::cout << "salut" << '\n';
    /*send(sock, "QUIT :leaving\r\n", 16, 0);
    close(sock);*/
}

void	ft_charg_map(std::map<std::string, std::string> &map)
{
	map["kaboul"] = "afghanistan";
	map["pretoria"] = "afrique du sud";
	map["tirana"] = "albanie";
	map["alger"] = "algerie";
	map["berlin"] = "allemagne";
	map["andorre-la-vieille"] = "andorre";
	map["luanda"] = "angola";
	map["saint john\'s"] = "antigua-et-barbuda";
	map["riyad"] = "arabie saoudite";
	map["buenos aires"] = "argentine";
	map["erevan"] = "armenie";
	map["canberra"] = "australie";
	map["vienne"] = "autriche";
	map["bakou"] = "azerbaidjan";
	map["nassau"] = "bahamas";
	map["manama"] = "bahrein";
	map["dacca"] = "bangladesh";
	map["bridgetown"] = "barbade";
	map["bruxelles"] = "belgique";
	map["belmopan"] = "belize";
	map["porto-novo"] = "benin";
	map["thimphou"] = "bhoutan";
	map["minsk"] = "bielorussie";
	map["naypyidaw"] = "birmanie";
	map["sucre / la paz"] = "bolivie";
	map["sarajevo"] = "bosnie-herzegovine";
	map["gaborone"] = "botswana";
	map["brasilia"] = "bresil";
	map["bandar seri begawan"] = "brunei";
	map["sofia"] = "bulgarie";
	map["ouagadougou"] = "burkina";
	map["gitega"] = "burundi";
	map["phnom penh"] = "cambodge";
	map["yaounde"] = "cameroun";
	map["ottawa"] = "canada";
	map["praia"] = "cap-vert";
	map["bangui"] = "centrafrique";
	map["santiago"] = "chili";
	map["pekin"] = "chine";
	map["nicosie"] = "chypre";
	map["bogota"] = "colombie";
	map["moroni"] = "comores";
	map["brazzaville"] = "congo";
	map["kinshasa"] = "republique democratique du congo";
	map["avarua"] = "iles cook";
	map["pyongyang"] = "coree du nord";
	map["seoul"] = "coree du sud";
	map["san jose"] = "costa rica";
	map["yamoussoukro"] = "côte d\'ivoire";
	map["zagreb"] = "croatie";
	map["la havane"] = "cuba";
	map["copenhague"] = "danemark";
	map["djibouti"] = "djibouti";
	map["saint-domingue"] = "republique dominicaine";
	map["roseau"] = "dominique";
	map["le caire"] = "egypte";
	map["abou dabi"] = "emirats arabes unis";
	map["quito"] = "equateur";
	map["asmara"] = "erythree";
	map["madrid"] = "espagne";
	map["tallinn"] = "estonie";
	map["mbabane"] = "eswatini";
	map["washington"] = "etats-unis";
	map["addis abeba"] = "ethiopie";
	map["suva"] = "fidji";
	map["helsinki"] = "finlande";
	map["paris"] = "france";
	map["libreville"] = "gabon";
	map["banjul"] = "gambie";
	map["tbilissi"] = "georgie";
	map["accra"] = "ghana";
	map["athenes"] = "grece";
	map["saint-georges"] = "grenade";
	map["guatemala"] = "guatemala";
	map["conakry"] = "guinee";
	map["malabo"] = "guinee equatoriale";
	map["bissao"] = "guinee-bissao";
	map["georgetown"] = "guyana";
	map["port-au-prince"] = "haiti";
	map["tegucigalpa"] = "honduras";
	map["budapest"] = "hongrie";
	map["new delhi"] = "inde";
	map["jakarta"] = "indonesie";
	map["bagdad"] = "irak";
	map["teheran"] = "iran";
	map["dublin"] = "irlande";
	map["reykjavik"] = "islande";
	map["jerusalem"] = "israël";
	map["rome"] = "italie";
	map["kingston"] = "jamaique";
	map["tokyo"] = "japon";
	map["amman"] = "jordanie";
	map["nour-soultan"] = "kazakhstan";
	map["nairobi"] = "kenya";
	map["bichkek"] = "kirghizstan";
	map["bairiki"] = "kiribati";
	map["pristina"] = "kosovo";
	map["koweit"] = "koweit";
	map["vientiane"] = "laos";
	map["maseru"] = "lesotho";
	map["riga"] = "lettonie";
	map["beyrouth"] = "liban";
	map["monrovia"] = "liberia";
	map["tripoli"] = "libye";
	map["vaduz"] = "liechtenstein";
	map["vilnius"] = "lituanie";
	map["luxembourg"] = "luxembourg";
	map["skopje"] = "macedoine du nord";
	map["antananarivo"] = "madagascar";
	map["kuala lumpur"] = "malaisie";
	map["lilongwe"] = "malawi";
	map["male"] = "maldives";
	map["bamako"] = "mali";
	map["la valette"] = "malte";
	map["rabat"] = "maroc";
	map["delap-uliga-darrit"] = "iles marshall";
	map["port-louis"] = "maurice";
	map["nouakchott"] = "mauritanie";
	map["mexico"] = "mexique";
	map["palikir"] = "micronesie";
	map["chisinau"] = "moldavie";
	map["monaco"] = "monaco";
	map["oulan-bator"] = "mongolie";
	map["podgorica"] = "montenegro";
	map["maputo"] = "mozambique";
	map["windhoek"] = "namibie";
	map["yaren"] = "nauru";
	map["katmandou"] = "nepal";
	map["managua"] = "nicaragua";
	map["niamey"] = "niger";
	map["abuja"] = "nigeria";
	map["alofi"] = "niue";
	map["oslo"] = "norvege";
	map["wellington"] = "nouvelle-zelande";
	map["mascate"] = "oman";
	map["kampala"] = "ouganda";
	map["tachkent"] = "ouzbekistan";
	map["islamabad"] = "pakistan";
	map["melekeok"] = "palaos";
	map["panama"] = "panama";
	map["port moresby"] = "papouasie-nouvelle-guinee";
	map["assomption"] = "paraguay";
	map["amsterdam"] = "pays-bas";
	map["lima"] = "perou";
	map["manille"] = "philippines";
	map["varsovie"] = "pologne";
	map["lisbonne"] = "portugal";
	map["doha"] = "qatar";
	map["bucarest"] = "roumanie";
	map["londres"] = "royaume-uni";
	map["moscou"] = "russie";
	map["kigali"] = "rwanda";
	map["basseterre"] = "saint-christophe-et-nieves";
	map["castries"] = "sainte-lucie";
	map["saint-marin"] = "saint-marin";
	map["kingstown"] = "saint-vincent-et-les-grenadines";
	map["honiara"] = "salomon";
	map["san salvador"] = "salvador";
	map["apia"] = "samoa";
	map["sao tome"] = "sao tome-et-principe";
	map["dakar"] = "senegal";
	map["belgrade"] = "serbie";
	map["victoria"] = "seychelles";
	map["freetown"] = "sierra leone";
	map["singapour"] = "singapour";
	map["bratislava"] = "slovaquie";
	map["ljubljana"] = "slovenie";
	map["mogadiscio"] = "somalie";
	map["khartoum"] = "soudan";
	map["djouba"] = "soudan du sud";
	map["sri jayewardenepura-kotte"] = "sri lanka";
	map["stockholm"] = "suede";
	map["berne"] = "suisse";
	map["paramaribo"] = "suriname";
	map["damas"] = "syrie";
	map["douchanbe"] = "tadjikistan";
	map["dodoma"] = "tanzanie";
	map["ndjamena"] = "tchad";
	map["prague"] = "tchequie";
	map["bangkok"] = "thailande";
	map["dili"] = "timor oriental";
	map["lome"] = "togo";
	map["nuku\'alofa"] = "tonga";
	map["port-d\'espagne"] = "trinite-et-tobago";
	map["tunis"] = "tunisie";
	map["achgabat"] = "turkmenistan";
	map["ankara"] = "turquie";
	map["vaiaku"] = "tuvalu";
	map["kiev"] = "ukraine";
	map["montevideo"] = "uruguay";
	map["port-vila"] = "vanuatu";
	map["vatican"] = "vatican";
	map["caracas"] = "venezuela";
	map["hanoi"] = "vietnam";
	map["sanaa"] = "yemen";
	map["lusaka"] = "zambie";
	map["harare"] = "zimbabwe";
}

int ft_chr_port(std::string port)
{
	if (port[0] == '-')
	{
		std::cerr << "Error\nThe port must not be negative." << '\n';
		return -1;
	}
	for (char const &c : port)
	{
		if (std::isdigit(c) == false)
		{
			std::cerr << "Error\nPort is not number." << '\n';
			return -1;
		}
	}
	if (port.length() > 5 || atoi(port.c_str()) > 65535)
	{
		std::cerr << "Error\nPort should not exceed 65535." << '\n';
		return -1;
	}
	return atoi(port.c_str());
}

int main(int argc, char **argv)
{
	Stop = 0;
	atexit(cleanupFunction);
	std::signal(SIGINT, handle_signal);
	if (argc != 4)
	{
		std::cerr << "./botirc <address> <port> <password>" << '\n';
		return 1;	
	}
	int port = ft_chr_port(argv[2]);
	if (port == -1)
		return 1;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		std::cerr << "Error\nSocket creation failed." << '\n';
		return 1;
	}
	struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0)
	{
    	std::cerr << "Error\nInvalide ip." << '\n';
		close(sock);
        return 1;
    }
    // Copie de l'adresse IP résolue dans la structure sockaddr_in
    struct sockaddr_in serverAddress;
    memcpy(&serverAddress.sin_addr, &((struct sockaddr_in*)result->ai_addr)->sin_addr, sizeof(struct in_addr));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    freeaddrinfo(result);
	if (connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
	{
        std::cerr << "Error\nConnection to server failed." << '\n';
        close(sock);
        return -1;
    }
	std::string capLs = "CAP LS\r\n";
	std::string nick = "NICK capitalsbot\r\nUSER capitalsbot capitalsbot localhost :capitalsbot\r\n";
    std::string capEnd = "CAP END\r\n";
    send(sock, capLs.c_str(), capLs.size(), 0);
	char buffer[4096];
	int bytes;

	bytes = recv(sock, buffer, sizeof(buffer), 0);
	buffer[bytes] = '\0';
	if (std::strcmp (buffer, "CAP * LS :\r\n") != 0)
	{
		std::cerr << "Error\nsocket binding to failed." << '\n';
		send(sock, "QUIT :leaving\r\n", 16, 0);
		close(sock);
		return 1;
	}
	capLs = "PASS " + std::string (argv[3]) + "\r\n";
	send(sock, capLs.c_str(), capLs.size(), 0);
	bytes = recv(sock, buffer, sizeof(buffer), 0);
	buffer[bytes] = '\0';
	if (std::strcmp(buffer, ":server 464  :password incorrect\r\n") == 0)
	{
		std::cerr << "Error\nPassword incorrect" << '\n';
		send(sock, "QUIT :leaving\r\n", 16, 0);
		close(sock);
		return 1;
	}
	else if (std::strcmp(buffer, ":localhost 001  :Password Correct\r\n") != 0)
	{
		std::cerr << "Error\nError when receiving packet password."	<< '\n';
		send(sock, "QUIT :leaving\r\n", 16, 0);
		close(sock);
		return 1;
	}
	send(sock, nick.c_str(), nick.size(), 0);
	send(sock, capEnd.c_str(), capEnd.size(), 0);
	bytes = recv(sock, buffer, sizeof(buffer), 0);
	buffer[bytes] = '\0';
	if (std::strstr (buffer, ":localhost 001 capitalsbot :Welcome to the IRC server\r\n") == NULL)
	{
		std::cerr << "Error\nsocket binding to failed. Welcome message." << '\n';
		send(sock, "QUIT :leaving\r\n", 16, 0);
		close(sock);
		return 1;
	}
	if (std::strstr(buffer, "CAP * LS :\r\n") == NULL)
	{
		bytes = recv(sock, buffer, sizeof(buffer), 0);
		buffer[bytes] = '\0';
		if (std::strcmp (buffer, "CAP * LS :\r\n") != 0)
		{
			std::cerr << "Error\nsocket binding to failed. CAP LS." << '\n';
			send(sock, "QUIT :leaving\r\n", 16, 0);
			close(sock);
			return 1;
		}
	}
	send(sock, "JOIN #pays\r\n", 13, 0);
	bytes = recv(sock, buffer, sizeof(buffer), 0);
	buffer[bytes] = '\0';
	if (std::strstr(buffer, "JOIN #pays\r\n") == NULL)
	{
		std::cout << buffer << '\n';
		std::cerr << "Error\nimpossible to connect to Chanel : #pays." << '\n';
		send(sock, "QUIT :leaving\r\n", 16, 0);
		close(sock);
		return 1;
	}
	std::map<std::string, std::string> map;
	ft_charg_map(map);
	int size_pays = map.size();
	int size_pays_find = 0;
	struct pollfd fds[1];
    fds[0].fd = sock;
    fds[0].events = POLLIN;
	while (Stop == 0)
	{
		if (poll(fds, 1, 100) != 1)
			continue ;
		bytes = recv(sock, buffer, sizeof(buffer), 0);
		buffer[bytes] = '\0';
		if (bytes == 0)
		{
			close(sock);
			return 0;
		}
		if (char *msg = std::strstr(buffer, " PRIVMSG #pays :"))
		{
			std::string searchKey = msg + 16;
			size_t found = searchKey.find("\r\n");
			searchKey.erase(found, 2);
   			std::map<std::string, std::string>::iterator it = map.find(searchKey);
			if (it != map.end()) 
			{
				size_pays_find ++;
				std::string message = "PRIVMSG #pays :play well " + searchKey + " and the capital of " + it->second + " " + std::to_string(size_pays_find) + "\\" + std::to_string(size_pays) + "\r\n";
				send(sock, message.c_str(), message.size(), 0);
				map.erase(searchKey);
			}
		}
		else if (std::strstr(buffer, " QUIT  :Stop Server") != NULL)
		{
			std::cout << "Server irc close." << '\n';
			close(sock);
			return 0;
		}
		else if (std::strstr(buffer, " KICK #pays+ capitalsbot") != NULL)
		{
			std::cout << "the bot was kicked from the server." << '\n';
			send(sock, "QUIT :leaving\r\n", 16, 0);
			close(sock);
			return 0;
		}
		else
			std::cout << buffer << '\n';
	}
	send(sock, "QUIT :leaving\r\n", 16, 0);
    close(sock);
	return 0;
}
