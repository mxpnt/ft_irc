#include "../incs/clientClass.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

Client::Client()
{
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
