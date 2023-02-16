#include "irc.hpp"

size_t Recv(char* buffer, size_t size, int socket) {
    size_t total = 0, n = 0;
    if ((n = recv(socket, buffer+total, size-total-1, 0)) > 0) {
        total += n;
    }
    buffer[total] = 0;
    return total;
}

void	wait_client(int server_socket)
{
	data	data;

	data.pollVec.push_back(poll_init(server_socket));
	while (1)
	{
		int	pollResult = poll(&data.pollVec[0], data.pollVec.size(), 1800);
		if (pollResult > 0)
		{
			if (data.pollVec[0].revents & POLLIN)
			{
				struct sockaddr_in	client_addr;
				int					c_addr_len = sizeof(client_addr);
				int					client_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&c_addr_len);

				std::cout << "accept success " << inet_ntoa(client_addr.sin_addr) << std::endl;
				struct pollfd newPollfd;
				newPollfd.fd = client_socket;
				newPollfd.events = POLLIN;
				data.pollVec.push_back(newPollfd);
			}
			std::vector<struct pollfd>::iterator it = data.pollVec.begin();
			it++;
			while (it != data.pollVec.end())
			{
				if ((*it).fd > 0 && (*it).revents & POLLIN)
				{
					char	buff[10000];
					Recv(buff, sizeof(buff), (*it).fd);
					std::cout << buff;
				}
				it++;
			}
		}
	}
}

