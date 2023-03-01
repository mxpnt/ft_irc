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
