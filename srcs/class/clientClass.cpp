#include "../../incs/clientClass.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

Client::Client(std::vector<struct pollfd> &tab_pollfd, int socket)
{
	tab_pollfd.resize(tab_pollfd.size() + 1);
	tab_pollfd.back().fd = socket;
	tab_pollfd.back().events = POLLIN;
	tab_pollfd.back().revents = 0;
	
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

std::string operator+(Client client, std::string str2)
{
	std::string str;

	str = (std::string)":" + client.getUser() + str2;
	return (str);
}

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

void	Client::set_registered(bool n)
{
	this->registered = n;
}

void	Client::set_server_password_sent(std::string password)
{
	this->server_password_sent = password;
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

int	Client::get_fd() const
{
	return (this->fd);
}

bool Client::get_registered() const
{
	return (this->registered);
}

std::string	Client::get_server_password_sent() const
{
	return (this->server_password_sent);
}
