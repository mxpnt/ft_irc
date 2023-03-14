#include "../../incs/clientClass.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

Client::Client(vector<struct pollfd> &tab_pollfd, int socket, string ip)
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

ostream &operator<<(ostream &os, Client const &obj)
{
	os << obj.getUser() << endl;
	return (os);
}

Client& operator<<(Client& client, string str)
{
	write(client.getFd(), str.c_str(), str.size());
	return client;
}

/***** member *****/

void    Client::numeric_reply(string numeric, string description)
{
    *this << ":" << SERVER_NAME << " " << numeric << " " << this->nick << " " << description << "\n";
}

void	Client::reply(Client* sender, string cmd, string dst, string description)
{
	*this << ":" << sender->nick << "!" << sender->user << "@" << sender->ip << " " << cmd << " ";
	if (!dst.empty())
		*this << dst << " ";
	*this << ":" << description << "\n";
}
//exemple :sdsed!~shshs@46.231.218.157 NICK :oui

/***** SETTERS *****/

void	Client::setUser(string u)
{
	this->user = u;
}

void	Client::setNick(string n)
{
	this->nick = n;
}

void	Client::setRealname(string rn)
{
	this->realname = rn;
}

void	Client::setServerPassword(string password)
{
	this->server_password = password;
}

/***** GETTERS *****/

string	Client::getUser() const
{
	return (this->user);
}

string	Client::getNick() const
{
	return (this->nick);
}

string	Client::getRealname() const
{
	return (this->realname);
}

int	Client::getFd() const
{
	return (this->fd);
}

string	Client::getServerPassword() const
{
	return (this->server_password);
}

string Client::getIp() const
{
	return (this->ip);
}
