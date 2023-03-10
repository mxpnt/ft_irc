#include "../../incs/clientClass.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

Client::Client(std::vector<struct pollfd> &tab_pollfd, int socket)
{
	tab_pollfd.resize(tab_pollfd.size() + 1);
	tab_pollfd.back().fd = socket;
	tab_pollfd.back().events = POLLIN;
	tab_pollfd.back().revents = 0;
	
	this->nick = "*";
	this->fd = socket;
	this->registered = 0;
}

Client::Client(std::vector<struct pollfd> &tab_pollfd, int socket, std::string ip)
{
	tab_pollfd.resize(tab_pollfd.size() + 1);
	tab_pollfd.back().fd = socket;
	tab_pollfd.back().events = POLLIN;
	tab_pollfd.back().revents = 0;
	
	this->nick = "*";
	this->ip = ip;
	this->fd = socket;
	this->registered = 0;
}

Client::Client(Client const &f)
{
	*this = f;
}

Client::~Client()
{
}

/***** OPERATORS *****/

Client	&Client::operator=(Client const &rhs)
{
	this->user = rhs.user;
	this->nick = rhs.nick;
	return (*this);
}

std::ostream &operator<<(std::ostream &os, Client const &obj)
{
	os << obj.getUser() << std::endl;
	return (os);
}

Client& operator<<(Client& client, std::string str)
{
	write(client.getFd(), str.c_str(), str.size());
	return client;
}

/***** member *****/

void    Client::numeric_reply(std::string numeric, std::string description)
{
    *this << ":" << SERVER_NAME << " " << numeric << " " << this->nick << " " << description << "\n";
}

void	Client::reply(Client* sender, std::string cmd, std::string dst, std::string description)
{
	*this << ":" << sender->nick << "!" << sender->user << "@" << sender->ip << " " << cmd << " ";
	if (!dst.empty())
		*this << dst << " ";
	*this << ":" << description << "\n";
}
//exemple :sdsed!~shshs@46.231.218.157 NICK :oui

/***** SETTERS *****/

void	Client::setUser(std::string u)
{
	this->user = u;
}

void	Client::setNick(std::string n)
{
	this->nick = n;
}

void	Client::setRealname(std::string rn)
{
	this->realname = rn;
}

void	Client::setServerPassword(std::string password)
{
	this->server_password = password;
}

/***** GETTERS *****/

std::string	Client::getUser() const
{
	return (this->user);
}

std::string	Client::getNick() const
{
	return (this->nick);
}

std::string	Client::getRealname() const
{
	return (this->realname);
}

int	Client::getFd() const
{
	return (this->fd);
}

std::string	Client::getServerPassword() const
{
	return (this->server_password);
}

std::string Client::getIp() const
{
	return (this->ip);
}
