#include "irc.hpp"

int	main(int argc, char **argv)
{
	int				server;
	long			conv;
	int				port;
	data			data;
	(void) argv;
	if (argc != 3)	{
		std::cout << "Wrong number of arguments" << std::endl;
		return (1);
	}
	conv = strtol(argv[1], 0, 10);
	if (errno != 0 || conv > 65536 || conv < 1 || is_number(argv[1])) {
		if (errno != 0)
			perror("strtol()");
		else
			std::cout << "Port invalid" << std::endl;
		return (2);
	}
	port = conv;
	server = create_server(port, argv[2]);
	data.popol.push_back(popoll(server));
	while (1)
	{
		int pollresult = poll(&(data.popol[0]), data.popol.size(), 18000);
		if (pollresult > 0)
		{
			if (data.popol[0].revents & POLLIN)
			{
				struct pollfd *newpoll = new struct pollfd;
				struct sockaddr_in	cliaddr;
				int					addrlen = sizeof(cliaddr);
				int					client_socket = accept(server, (struct sockaddr *)&cliaddr, (unsigned int*)&addrlen);
				(void) client_socket;
				std::cout << "accept success " << inet_ntoa(cliaddr.sin_addr) << std::endl;
				newpoll->fd = server;
				newpoll->events = POLLIN;
				data.popol.push_back(*newpoll);
			}
			std::vector<struct pollfd>::iterator it = data.popol.begin();
			while (it != data.popol.end())
			{
				if ((*it).revents & POLLIN)
				{
					char str[1002];
					int r = recv((*it).fd, str, 1000, 0);
					std::cout << r << std::endl;
					if (r == 0 || r == -1)
					{
						// data.popol.erase(it);
						// it = data.popol.begin();
						std::cout << "oui" << std::endl;
					}
					else
					{
						std::cout << "non" << std::endl;
						str[1001] = 0;
						std::cout << str << std::endl;
					}
				}
				it++;
			}
		}
	}
	return (0);
}
