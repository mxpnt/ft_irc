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
	this->msg = s.split(' ');
	
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
	this->cmd["PRIVMSG"] = 0;
	this->cmd["PING"] = 0;
	this->cmd["NOTICE"] = 0;
	this->cmd["QUIT"] = 0;
	
	//oper command
	this->cmd["KICK"] = 0;
	this->cmd["MODE"] = 0;
	this->cmd["INVITE"] = 0;
	this->cmd["TOPIC"] = 0;
}

command_ptr	Commands::cmd_match()
{
	// for (size_t i = 0; i < this->msg.size(); ++i)
	// 	cout << this->msg[i];
	if (msg.size())
	{
		if (cmd.find(msg[0]) != cmd.end())
			return(cmd.find(msg[0])->second);
	}
	return (0);
}
