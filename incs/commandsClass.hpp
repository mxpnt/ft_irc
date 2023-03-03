#ifndef COMMANDSCLASS_HPP
# define COMMANDSCLASS_HPP

# include "irc.hpp"

class	Client;
class	Commands;

typedef int (Commands::*command_ptr)(std::vector<Client*>&, Client*);

class	Commands {
private:
	std::map<std::string, command_ptr>	cmd;
	std::vector<std::string>	msg;
	std::string					name;
	std::string					server_password;

	void	init_map();
public:
	Commands();
	Commands(Commands const &f);
	Commands(std::string s, std::string server_password);
	~Commands();

	Commands	&operator=(Commands const &rhs);

	command_ptr	cmd_match();
	int		cmd_user(std::vector<Client*> &repertory, Client *client);
	int		cmd_nick(std::vector<Client*> &repertory, Client *client);
	int		cmd_pass(std::vector<Client*> &repertory, Client *client);
};

#endif