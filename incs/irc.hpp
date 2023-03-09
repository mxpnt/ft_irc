#ifndef IRC_HPP
# define IRC_HPP

# define SERVER_IP "10.14.7.7"
# define SERVER_NAME "irc.42"
# define NETWORK_NAME "42"
# define VERSION "1.0"

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
# include <sstream>

# include "splitstringClass.hpp"
# include "commandsClass.hpp"
# include "clientClass.hpp"

/***** server.cpp *****/
int     create_server(int port);

/***** client.cpp *****/
void    wait_client(int server_socket, std::string server_password);

/***** register.cpp *****/
void    register_process(std::vector<Client*> repertory, Client* client);

/***** command_manage.cpp *****/
void    command_manage(std::vector<Client*> repertory, int fd, char* buff);

/***** is_number.cpp *****/
int     is_number(std::string str);

template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

#endif