#ifndef CLIENTCLASS_HPP
# define CLIENTCLASS_HPP

# include "irc.hpp"

class	Client	{
private:
	std::string		user;
	std::string		nick;
	std::string		realname;
	std::string		server_password_sent;
	std::string		ip;
	int				fd;
	bool			registered;

public:
	Client(std::vector<struct pollfd> &tab_pollfd, int socket);
	Client(std::vector<struct pollfd> &tab_pollfd, int socket, std::string ip);
	Client(Client const &f);
	~Client();

	Client	&operator=(Client const &rhs);

	void	numeric_reply(std::string numeric, std::string description);
	void	reply(Client* sender, std::string cmd, std::string dst, std::string description);

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
	std::string get_ip() const;
};

std::ostream &operator<<(std::ostream &os, Client const &obj);
Client& operator<<(Client& client, std::string str);

#endif