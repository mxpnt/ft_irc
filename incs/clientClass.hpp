#ifndef CLIENTCLASS_HPP
# define CLIENTCLASS_HPP

# include "irc.hpp"

class	Client	{
private:
	std::string		user;
	std::string		nick;
	bool		connected;

	struct pollfd*	addr_pollfd;

public:
	Client(std::list<struct pollfd> tab_pollfd, int socket);
	Client(Client const &f);
	~Client();

	Client	&operator=(Client const &rhs);

	struct pollfd*	get_pollfd();
	static std::vector<struct pollfd> get_polltab();
};

#endif