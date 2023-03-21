#include "bot.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

Bot::Bot()
{
}

Bot::Bot(std::string addr, long port, std::string pwd)
{
	this->server_addr = addr;
	this->port = port;
	this->password = pwd;

	this->user = "Bot";
	this->nick = "Bot_Shady";
	this->realname = "Bot";

	this->isRegistered = 0;
}

Bot::Bot(Bot const &f)
{
	*this = f;
}

Bot::~Bot()
{
}

/***** OPERATORS *****/

Bot	&Bot::operator=(Bot const &rhs)
{
	this->server_addr = rhs.server_addr;
	this->port = rhs.port;
	this->password = rhs.password;

	this->user = rhs.user;
	this->nick = rhs.nick;
	this->realname = rhs.realname;
	this->pollfd = rhs.pollfd;
	this->addr = rhs.addr;

	this->isRegistered = rhs.isRegistered;

	return (*this);
}

/***** MEMBER FUNCTIONS *****/

void	Bot::sendMsg(std::string msg) const
{
	if (pollfd.revents & POLLOUT) {
		if (send(pollfd.fd, msg.c_str(), msg.size(), 0) < 0)
			perror("send()");
	}
}

size_t Bot::Recv(char* buffer, size_t size, int socket)
{
    size_t total = 0, n = 0;
    if ((n = recv(socket, buffer + total, size - total - 1, 0)) > 0)
        total += n;
    buffer[total] = 0;
    return (total);
}

void	Bot::launch()
{
	this->pollfd.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->pollfd.fd < 0)	{
		perror("socket()");
		exit(1);
	}
	this->addr.sin_family = AF_INET;
	this->addr.sin_port = htons(port);
	this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
	pollfd.events = POLLIN | POLLOUT;
	if (fcntl(this->pollfd.fd, F_SETFL, O_NONBLOCK) < 0) {
		perror("fcntl()");
		exit(1);
	}
	connect(this->pollfd.fd, (struct sockaddr*)&addr, sizeof(addr));
}

void	Bot::run()
{
	while (1)
	{
		int	pollResult = poll(&pollfd, 1, 0);
		if (pollResult > 0)
		{
			if (!isRegistered && pollfd.revents & POLLOUT)
			{
				std::string	line;
				line = "USER " + user + " 0 * :" + realname + "\r\n";
				sendMsg(line);
				line = "NICK " + nick + "\r\n";
				sendMsg(line);
				line = "PASS " + password + "\r\n";
				sendMsg(line);
				isRegistered = 1;
			}
			else if (pollfd.revents & POLLIN)
			{
				char	buff[512];
				if (Recv(buff, sizeof(buff), pollfd.fd) == 0)
				{
					std::cerr << "Connection closed" << std::endl;
					break ;
				}
			}
		}
	}
}
