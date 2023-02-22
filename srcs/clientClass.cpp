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
