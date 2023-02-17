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

Commands::Commands(SplitString s)
{
	this->msg = s.split(' ');
	init_map();
}

Commands::~Commands()
{
}

/***** OPERATORS *****/

Commands	&Commands::operator=(Commands const &rhs)
{
	return (*this);
}

/***** MEMBER FUNCTIONS *****/

void	Commands::init_map()
{
	this->cmd["USER"] = ;
	this->cmd["NICK"] = ;
	this->cmd["JOIN"] = ;
	this->cmd["PRIVMSG"] = ;
}
