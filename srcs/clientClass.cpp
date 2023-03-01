#include "../incs/clientClass.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

Client::Client(std::list<struct pollfd> tab_pollfd, int socket)
{
	tab_pollfd.push_back({socket, POLLIN, POLLIN});
	this->addr_pollfd = &tab_pollfd.back();
}

Client::Client(Client const &f)
{
	*this = f;
}

Client::~Client()
{
}

struct pollfd*	Client::get_pollfd()
{
	return (this->addr_pollfd);
}

/***** OPERATORS *****/

Client	&Client::operator=(Client const &rhs)
{
	this->user = rhs.user;
	this->nick = rhs.nick;
	return (*this);
}

/***** SETTERS *****/

void	Client::setID(int i)
{
	this->id = i;
}

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

int	Client::getID() const
{
	return (this->id);
}
