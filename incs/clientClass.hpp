#ifndef CLIENTCLASS_HPP
# define CLIENTCLASS_HPP

# include "irc.hpp"

class	Client	{
private:
	std::string		user;
	std::string		nick;
	std::string		realname;
	int				id;
	int				fd;
	bool			connected;

public:
	Client(std::vector<struct pollfd> &tab_pollfd, int socket);
	Client(Client const &f);
	~Client();

	Client	&operator=(Client const &rhs);

	void	setID(int i);
	void	setUser(std::string u);
	void	setNick(std::string n);
	void	setRealname(std::string rn);
	void	set_connected(bool n);

	std::string	getUser() const;
	std::string	getNick() const;
	std::string	getRealname() const;
	int			getID() const;
	int			get_fd() const;
	bool		get_connected() const;
};

std::ostream &operator<<(std::ostream &os, Client const &obj);

#endif