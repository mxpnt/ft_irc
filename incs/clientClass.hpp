#ifndef CLIENTCLASS_HPP
# define CLIENTCLASS_HPP

# include "irc.hpp"

class	Client	{
private:
	std::string		user;
	std::string		nick;
	std::string		realname;
	std::string		server_password_sent;
	int				fd;
	bool			registered;

public:
	Client(std::vector<struct pollfd> &tab_pollfd, int socket);
	Client(Client const &f);
	~Client();

	Client	&operator=(Client const &rhs);

	void	setUser(std::string u);
	void	setNick(std::string n);
	void	setRealname(std::string rn);
	void	set_registered(bool n);
	void	set_server_password_sent(std::string password);

	std::string	getUser() const;
	std::string	getNick() const;
	std::string	getRealname() const;
	int			get_fd() const;
	bool		get_registered() const;
	std::string	get_server_password_sent() const;
};

std::ostream &operator<<(std::ostream &os, Client const &obj);
std::string operator+(Client client, std::string str2);

#endif