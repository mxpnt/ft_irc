#include "../../incs/commandsClass.hpp"

int	Commands::cmd_nick(std::vector<Client*> &repertory, Client *client)
{
	(void) repertory;
	if (msg.size() < 2)
	{
		std::cerr << "ERR_NONICKNAMEGIVEN" << std::endl;
		return (1);
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
