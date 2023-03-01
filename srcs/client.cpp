#include "../incs/irc.hpp"

size_t Recv(char* buffer, size_t size, int socket)
{
    size_t total = 0, n = 0;
    if ((n = recv(socket, buffer + total, size - total - 1, 0)) > 0)
        total += n;
    buffer[total] = 0;
    return (total);
}

void	new_client(int server_socket, std::list<struct pollfd> tab_pollfd, std::vector<Client*> &repertory)
{
	struct sockaddr_in	client_addr;
	int					c_addr_len = sizeof(client_addr);
	int					client_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&c_addr_len);

	std::cout << "accept success " << inet_ntoa(client_addr.sin_addr) << std::endl;
	repertory.push_back(new Client(tab_pollfd, client_socket));
}

void	wait_client(int server_socket)
{
	std::vector<Client*>		repertory;
	std::vector<Client*>::iterator vit;
	std::list<struct pollfd>	tab_pollfd;
	std::list<struct pollfd>::iterator lit;

	int		i = 0;

	repertory.push_back(new Client(tab_pollfd, server_socket));
	while (1)
	{
		int	pollResult = poll(&tab_pollfd.front(), tab_pollfd.size(), 1800);
		if (pollResult > 0)
		{
			if (repertory[0]->get_pollfd()->revents & POLLIN)	{
				new_client(server_socket, tab_pollfd, repertory);
			}

			vit = repertory.begin();
			lit = tab_pollfd.begin();
			vit++;
			lit++;
			while (vit != repertory.end())
			{
				if ((*vit)->get_pollfd()->fd > 0 && (*vit)->get_pollfd()->revents & POLLIN)
				{
					if (i++ == 0)
						break;
					char	buff[512];
					if (Recv(buff, sizeof(buff), (*vit)->get_pollfd()->fd) == 0)
					{
						std::cout << "bye" << std::endl;
						delete *vit;
						repertory.erase(vit);
						tab_pollfd.erase(lit);
						continue;
					}
					std::cout << buff;
					//Commands	c(buff);
					//c.cmd_match();
					// write((*it).fd, "ERR_PASSWDMISMATCH", 18);
				}
				vit++;
				lit++;
			}
		}
	}
}
