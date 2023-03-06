#include "../../incs/commandsClass.hpp"

void	Commands::cmd_nick(std::vector<Client*> &repertory, Client *client)
{
	(void) repertory;
	std::string	str;
	
	if (msg.size() < 2)
	{
		std::cerr << "ERR_NONICKNAMEGIVEN" << std::endl;
		return ;
	}
	/* CHECK SI NICK DEJA UTILISE */
	if (msg[0] == "NICK" && msg[1] == "DEJA UTILISE")
	{
		std::cerr << "ERR_NICKNAMEINUSE" << std::endl;
		return ;
	}
	if (client->get_registered())
		client->reply(client, "NICK", "", this->msg[1]);
	client->setNick(msg[1]);
}
