#ifndef BOT_HPP
# define BOT_HPP

# include "iostream"
# include <netinet/in.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <poll.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
// # include <stdio.h>
# include <stdlib.h>
# include <time.h>

# include "splitstringClass.hpp"

class	Bot	{
private:
	std::string			server_addr;
	long				port;
	std::string			password;

	std::string			user;
	std::string			nick;
	std::string			realname;
	struct pollfd				pollfd;
	struct sockaddr_in	addr;
public:
	Bot();
	Bot(std::string addr, long port, std::string pwd);
	Bot(Bot const &f);
	~Bot();

	Bot	&operator=(Bot const &rhs);

	void		sendMsg(std::string msg) const;
	size_t		Recv(char* buffer, size_t size, int socket);
	void		launch();
	void		run();
	void		message_manage(std::string msg);
	std::string	randomMsg();

	bool	isRegistered;
	std::string	buffer;
};

#endif