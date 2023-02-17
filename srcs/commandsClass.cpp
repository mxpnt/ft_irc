#include "../incs/commandsClass.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

Commands::Commands()
{
	cmd[0] = "USER ";
	cmd[1] = "NICK ";
	cmd[2] = "JOIN ";
	cmd[3] = "PRIVMSG ";
}

Commands::Commands(Commands const &f)
{
	*this = f;
}

Commands::Commands(std::vector<std::string> vmsg)
{
}

Commands::~Commands()
{
}

/***** OPERATORS *****/

Commands	&Commands::operator=(Commands const &rhs)
{
	this->cmd[0] = rhs.cmd[0];
	this->cmd[1] = rhs.cmd[1];
	this->cmd[2] = rhs.cmd[2];
	this->cmd[3] = rhs.cmd[3];
	this->msg = rhs.msg;
	return (*this);
}