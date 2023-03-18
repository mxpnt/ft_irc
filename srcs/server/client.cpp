#include "../../incs/irc.hpp"

size_t Recv(char* buffer, size_t size, int socket)
{
    size_t total = 0, n = 0;
    if ((n = recv(socket, buffer + total, size - total - 1, 0)) > 0)
        total += n;
    buffer[total] = 0;
    return (total);
}

void	wait_client(pair<int, string> server_socket_and_ip, string server_password)
{
	vector<Client*>		repertory;
	vector<struct pollfd>	tab_pollfd;
	vector<struct pollfd>::iterator it;

	int		i = 0;

	repertory.push_back(new Client(tab_pollfd, server_socket_and_ip.first, server_socket_and_ip.second));
	repertory[0]->setServerPassword(server_password);
	while (1)
	{
		int	pollResult = poll(&tab_pollfd[0], tab_pollfd.size(), 1800);
		if (pollResult > 0)
		{
			if (tab_pollfd[0].revents & POLLIN)	{
				new_client(repertory[0]->getFd(), tab_pollfd, repertory);
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
						delete_client(repertory, (*it).fd, 0);
						tab_pollfd.erase(it);
						continue;
					}
					try
					{
						command_manage(repertory, (*it).fd, buff);
					}
					catch (exception &e)
					{
						delete_client(repertory, (*it).fd, 1);
						tab_pollfd.erase(it);
						continue;
					}

				}
				it++;
			}
		}
	}
	delete repertory[0];
}
