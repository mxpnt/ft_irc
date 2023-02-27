#ifndef CLIENTCLASS_HPP
# define CLIENTCLASS_HPP

# include "irc.hpp"

class	Client	{
private:
	struct pollfd	pofd;
	std::string		user;
	std::string		nick;
	bool		connected;

public:
	Client();
	Client(struct pollfd pollfd);
	Client(Client const &f);
	~Client();

	Client	&operator=(Client const &rhs);
};

#endif