#ifndef COMMANDSCLASS_HPP
# define COMMANDSCLASS_HPP

# include "irc.hpp"

class	Client;
class	Commands {
private:
	std::map<std::string, void (Commands::*)(std::vector<Client*> client, int fd)> cmd;
	std::vector<std::string>	msg;
	std::string					name;

	void	init_map();
public:
	Commands();
	Commands(Commands const &f);
	Commands(std::string s);
	~Commands();

	Commands	&operator=(Commands const &rhs);

	void *(Commands::)(std::vector<Client*>,int)	cmd_match(std::vector<Client*> client, int fd);
	void	cmd_user(std::vector<Client*> client, int fd);
	int		cmd_nick(Client *client);
};

#endif