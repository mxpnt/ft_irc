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
	this->cmd["USER"] = &Commands::cmd_user;
	this->cmd["NICK"] = 0;
	this->cmd["JOIN"] = 0;
	this->cmd["PRIVMSG"] = 0;
}

void (*Commands::)(std::vector<Client*>,int)	Commands::cmd_match(std::vector<Client*> client, int fd)
{
	for (size_t i = 0; i < this->msg.size(); ++i)
		std::cout << this->msg[i];

	(void) client, (void) fd;
	if (cmd.find(msg[0]) != cmd.end())
		return(&(cmd.find(msg[0])->second));
	return (0);
}

void	Commands::cmd_user(std::vector<Client*> client, int fd)
{
	std::vector<Client*>::iterator it = client.begin();
	while (it != client.end() && (*it)->getID() != fd)
		++it;
	if (it == client.end())
		return ;
	if ((*it)->getUser() != "")
		std::cerr << "ERR_ALREADYREGISTERED" << std::endl;
	else
	{
		int	len = msg.size();
		if (len > 3 && msg[2] == "0" && msg[3] == "*")
		{
			(*it)->setUser(msg[1]);
			std::cout << (*it)->getUser() << std::endl;
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
					(*it)->setRealname(realname);
				}
				else
				{
					/* choisir si ignorer apres 1 espace ou concatener */
					(*it)->setRealname(msg[4]);
				}
			}
		}
	}
}

int	Commands::cmd_nick(Client *client)
{
	if (msg.size() < 2)
	{
		std::cerr << "ERR_NONICKNAMEGIVEN" << std::endl;
		return (431);
	}
	/* CHECK SI NICK DEJA UTILISE */
	else if (msg[0] == "NICK" && msg[1] == "DEJA UTILISE")
	{
		std::cerr << "ERR_NICKNAMEINUSE" << std::endl;
	}
	else if (msg[0] == client->getUser() && msg[1] == "NICK" && msg[2] == "DEJA UTILISE")
	{
		std::cerr << "ERR_NICKNAMEINUSE" << std::endl;
	}
	else
	{
		if (msg[0] == "NICK")
			client->setNick(msg[1]);
		else if (msg[0] == client->getNick() && msg[1] == "NICK")
			client->setNick(msg[2]);
	}
	return (0);
}
