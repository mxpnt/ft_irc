#ifndef CLIENTCLASS_HPP
# define CLIENTCLASS_HPP

# include "irc.hpp"

class	Client	{
private:
	std::string	user;
	std::string	nick;
	bool		connected;
public:
	Client();
	Client(Client const &f);
	~Client();

	Client	&operator=(Client const &rhs);
};

#endif