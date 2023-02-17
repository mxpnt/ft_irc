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
# include <map>
# include <arpa/inet.h>

# include "splitstringClass.hpp"
# include "commandsClass.hpp"

/***** server.cpp *****/
int				create_server(int port, std::string password);
struct pollfd	poll_init(int server_socket);

/***** client.cpp *****/
void			wait_client(int server_socket);

/***** is_number.cpp *****/
int				is_number(std::string str);

/***** msg.cpp *****/
void			parsing_client_msg(char *str);

typedef struct s_data 
{
	std::vector<struct pollfd> pollVec;
} data;

#endif