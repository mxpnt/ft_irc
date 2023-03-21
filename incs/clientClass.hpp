#ifndef CLIENTCLASS_HPP
# define CLIENTCLASS_HPP

# include "irc.hpp"

class Channel;

class	Client	{
private:
	
	string		user;
	string		nick;
	string		realname;
	string		server_password;
	string		ip;
	int			fd;

public:
	Client(vector<struct pollfd> &tab_pollfd, int socket, string ip);
	Client(Client const &f);
	~Client();

	Client	&operator=(Client const &rhs);

	string				buff;
	bool				registered;
	vector<Channel*>	channels;
	vector<Channel*>	invite_recv;

	void	numeric_reply(string numeric, string description);
	void	reply(Client* sender, string cmd, string dst, string description);

	void	setUser(string u);
	void	setNick(string n);
	void	setRealname(string rn);
	void	setServerPassword(string password);

	string	getUser() const;
	string	getNick() const;
	string	getRealname() const;
	int		getFd() const;
	string	getServerPassword() const;
	string	getIp() const;
};

ostream &operator<<(ostream &os, Client const &obj);
Client& operator<<(Client& client, string str);

#endif