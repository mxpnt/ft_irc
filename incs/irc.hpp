#ifndef IRC_HPP
# define IRC_HPP

# define SERVER_NAME "irc.42"
# define NETWORK_NAME "42"
# define VERSION "1.0"
# define USERLEN 10

# include <iostream>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <poll.h>
# include <vector>
# include <map>
# include <arpa/inet.h>
# include <sstream>

using namespace std;

# include "splitstringClass.hpp"
# include "commandsClass.hpp"
# include "clientClass.hpp"
# include "channelClass.hpp"

/***** server.cpp *****/
pair<int, string>	create_server(int port);

/***** client.cpp *****/
void    wait_client(pair<int, string> server_socket_and_ip, string server_password);

/***** client_manage.cpp *****/
void	delete_client(vector<Client*>& repertory, int fd, int fd_good);
void	new_client(int server_socket, vector<struct pollfd> &tab_pollfd, vector<Client*> &repertory);
Client* find_client(vector<Client*> &repertory, int fd);
Client*	find_client(vector<Client*> &repertory, string name);

/***** register.cpp *****/
void    register_process(vector<Client*> repertory, Client* client);

/***** command_manage.cpp *****/
void    command_manage(vector<Client*> repertory, int fd, string buff);

/***** join_cmd.cpp *****/
Channel* 		find_channel(vector<Channel*>& channels, string name);
vector<string>	create_chans_name_tab(vector<Channel*>& all_chans);

/***** is_alphanum.cpp *****/
int     is_number(string str);
int     is_alpha(string str);
int     is_alphanum(string str);

template < typename T > string to_string( const T& n )
{
    ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

#endif