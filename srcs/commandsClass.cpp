#include "../incs/commandsClass.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

Commands::Commands()
{
	init_map();
}

Commands::Commands(Commands const &f)
{
	*this = f;
}

Commands::Commands(std::string str)
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
	this->cmd["USER"] = 0;
	this->cmd["NICK"] = 0;
	this->cmd["JOIN"] = 0;
	this->cmd["PRIVMSG"] = 0;
}

void*	Commands::cmd_match()
{
	for (size_t i = 0; i < this->msg.size(); ++i)
		std::cout << i << " = "<< this->msg[i] << std::endl;
	
	if (cmd.find(msg[0]) != cmd.end())
		return(&cmd.find(msg[0])->second);
	return (0);
}
