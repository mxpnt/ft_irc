#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <stdio.h>
# include <errno.h>
# include <string>
# include <unistd.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <poll.h>
# include <vector>
# include <arpa/inet.h>

/***** server.cpp *****/
int				create_server(int port, std::string password);
struct pollfd	popoll(int server);

/***** is_number.cpp *****/
int				is_number(std::string str);

typedef struct s_data 
{
	std::vector<struct pollfd> popol;
} data;

#endif