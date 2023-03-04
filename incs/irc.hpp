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
# include "clientClass.hpp"

/***** server.cpp *****/
int				create_server(int port);

/***** client.cpp *****/
void			wait_client(int server_socket, std::string server_password);

/***** command_manage.cpp *****/
void            command_manage(std::vector<Client*> repertory, int fd, char* buff, std::string server_password);

/***** is_number.cpp *****/
int				is_number(std::string str);

#endif