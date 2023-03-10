#ifndef IRC_HPP
# define IRC_HPP

# define SERVER_NAME "irc.42"
# define NETWORK_NAME "42"
# define VERSION "1.0"
# define USERLEN 10

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
# include <utility>
# include <arpa/inet.h>
# include <sstream>

# include "splitstringClass.hpp"
# include "commandsClass.hpp"
# include "clientClass.hpp"
# include "channelClass.hpp"

/***** server.cpp *****/
std::pair<int, std::string>    create_server(int port);

/***** client.cpp *****/
void    wait_client(std::pair<int, std::string> server_socket_and_ip, std::string server_password);

/***** register.cpp *****/
void    register_process(std::vector<Client*> repertory, Client* client);

/***** command_manage.cpp *****/
void    command_manage(std::vector<Client*> repertory, int fd, char* buff);

/***** is_alphanum.cpp *****/
int     is_number(std::string str);
int     is_alpha(std::string str);
int     is_alphanum(std::string str);

/***** is_valid_nick.cpp *****/
int		is_valid_nick(std::string nick);

template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

#endif