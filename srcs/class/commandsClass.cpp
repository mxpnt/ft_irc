#include "../../incs/commandsClass.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

Commands::Commands()
{
	init_map();
}

Commands::Commands(Commands const &f)
{
	*this = f;
}

Commands::Commands(string str)
{
	SplitString	s(str.c_str());
	this->msg = s.cmd_split(" ");
	
	init_map();
}

Commands::~Commands()
{
}

/***** OPERATORS *****/

Commands	&Commands::operator=(Commands const &rhs)
{
	this->cmd = rhs.cmd;
	this->msg =rhs.msg;
	this->name = rhs.name;
	return (*this);
}

/***** MEMBER FUNCTIONS *****/

void	Commands::init_map()
{
	this->cmd["USER"] = &Commands::cmd_user;
	this->cmd["NICK"] = &Commands::cmd_nick;
	this->cmd["PASS"] = &Commands::cmd_pass;
	this->cmd["JOIN"] = &Commands::cmd_join;
	this->cmd["PRIVMSG"] = &Commands::cmd_privmsg;
	this->cmd["PING"] = &Commands::cmd_ping;
	this->cmd["PONG"] = &Commands::cmd_ping;
	this->cmd["NOTICE"] = 0;
	this->cmd["QUIT"] = &Commands::cmd_quit;
	
	//oper command
	this->cmd["KICK"] = &Commands::cmd_kick;
	this->cmd["MODE"] = &Commands::cmd_mode;
	this->cmd["INVITE"] = &Commands::cmd_invite;
	this->cmd["TOPIC"] = &Commands::cmd_topic;
}

command_ptr	Commands::cmd_match()
{
	if (msg.size())
	{
		if (cmd.find(msg[0]) != cmd.end())
			return(cmd.find(msg[0])->second);
	}
	return (0);
}
