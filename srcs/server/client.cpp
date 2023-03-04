#include "../../incs/irc.hpp"

size_t Recv(char* buffer, size_t size, int socket)
{
    size_t total = 0, n = 0;
    if ((n = recv(socket, buffer + total, size - total - 1, 0)) > 0)
        total += n;
    buffer[total] = 0;
    return (total);
}

void	new_client(int server_socket, std::vector<struct pollfd> &tab_pollfd, std::vector<Client*> &repertory)
{
	struct sockaddr_in	client_addr;
	int					c_addr_len = sizeof(client_addr);
	int					client_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&c_addr_len);

	std::cout << "accept success " << inet_ntoa(client_addr.sin_addr) << std::endl;
	repertory.push_back(new Client(tab_pollfd, client_socket));
}

void	delete_client(std::vector<Client*>& repertory, int fd)
{
	std::vector<Client*>::iterator	it = repertory.begin();

	while (it != repertory.end())
	{
		if ((*it)->get_fd() == fd)
		{
			delete *it;
			repertory.erase(it);
			return ;
		}
		it++;
	}
	std::cout << "delete_client() error: client fd not found" << std::endl;
}

void	wait_client(int server_socket, std::string server_password)
{
	std::vector<Client*>		repertory;
	std::vector<struct pollfd>	tab_pollfd;
	std::vector<struct pollfd>::iterator it;

	int		i = 0;

	repertory.push_back(new Client(tab_pollfd, server_socket));
	while (1)
	{
		int	pollResult = poll(&tab_pollfd[0], tab_pollfd.size(), 1800);
		if (pollResult > 0)
		{
			if (tab_pollfd[0].revents & POLLIN)	{
				new_client(server_socket, tab_pollfd, repertory);
			}

			it = tab_pollfd.begin();
			it++;
			while (it != tab_pollfd.end())
			{
				if ((*it).fd > 0 && (*it).revents & POLLIN)
				{
					if (i++ == 0)
						break;
					char	buff[512];
					if (Recv(buff, sizeof(buff), (*it).fd) == 0)
					{
						delete_client(repertory, (*it).fd);
						tab_pollfd.erase(it);
						continue;
					}
					try
					{
						command_manage(repertory, (*it).fd, buff, server_password);
					}
					catch (std::exception &e)
					{
						delete_client(repertory, (*it).fd);
						tab_pollfd.erase(it);
						continue;
					}

				}
				it++;
			}
		}
	}
}
