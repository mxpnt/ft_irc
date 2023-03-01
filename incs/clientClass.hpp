#ifndef CLIENTCLASS_HPP
# define CLIENTCLASS_HPP

# include "irc.hpp"

class	Client	{
private:
	struct pollfd	pofd;
	std::string		user;
	std::string		nick;
	std::string		realname;
	int				id;
	bool		connected;

public:
	Client();
	// Client(struct pollfd pollfd);
	Client(Client const &f);
	~Client();

	Client	&operator=(Client const &rhs);

	void	setID(int i);
	void	setUser(std::string u);
	void	setNick(std::string n);
	void	setRealname(std::string rn);

	std::string	getUser() const;
	std::string	getNick() const;
	std::string	getRealname() const;
	int			getID() const;
};

#endif