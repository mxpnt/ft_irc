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
		std::cout << this->msg[i];

	if (cmd.find(msg[0]) != cmd.end())
		return(&cmd.find(msg[0])->second);
	return (0);
}

void	Commands::cmd_user(Client *client)
{
	if (client->getUser() != "")
		std::cerr << "ERR_ALREADYREGISTERED" << std::endl;
	else
	{
		int	len = msg.size();
		if (len > 3 && msg[2] == "0" && msg[3] == "*")
		{
			client->setUser(msg[1]);
			if (len > 4)
			{
				if (msg[4][0] == ':')
				{
					std::string	realname;
					realname.append(msg[4]);
					for (int i = 5; i < len; ++i)
					{
						realname.append(" ");
						realname.append(msg[i]);
					}
					realname.erase(realname.begin());
					client->setRealname(realname);
				}
				else
				{
					/* choisir si ignorer apres 1 espace ou concatener */
					client->setRealname(msg[4]);
				}
			}
		}
	}
}
