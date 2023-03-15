#ifndef COMMANDSCLASS_HPP
# define COMMANDSCLASS_HPP

# include "irc.hpp"

class	Client;
class	Commands;

typedef void (Commands::*command_ptr)(vector<Client*>&, Client*);

class	Commands {
private:
	map<string, command_ptr>	cmd;
	vector<string>	msg;
	string					name;

	void	init_map();
public:
	Commands();
	Commands(Commands const &f);
	Commands(string s);
	~Commands();

	Commands	&operator=(Commands const &rhs);

	command_ptr	cmd_match();
	void		cmd_user(vector<Client*> &repertory, Client *client);
	void		cmd_nick(vector<Client*> &repertory, Client *client);
	void		cmd_pass(vector<Client*> &repertory, Client *client);
	void		cmd_join(vector<Client*> &repertory, Client *client);
	void		cmd_quit(vector<Client*> &repertory, Client *client);
	void		cmd_privmsg(vector<Client*> &repertory, Client *client);
};

#endif