#include "../../incs/commandsClass.hpp"

void	Commands::cmd_nick(std::vector<Client*> &repertory, Client *client)
{
	if (msg.size() < 2)
	{
		client->numeric_reply("431", "ERR_NONICKNAMEGIVEN");
		return ;
	}
	if (is_valid_nick(msg[1]))
	{
		client->numeric_reply("432", ":Erroneus nickname");
		return ;
	}
	std::vector<Client*>::iterator	it = repertory.begin();
	while (it != repertory.end())
	{
		if (msg[1] == (*it)->getNick())
		{
			client->numeric_reply("433", ":Nickname is already in use");
			return ;
		}
		++it;
	}
	if (client->getRegistered())
		client->reply(client, "NICK", "", this->msg[1]);
	client->setNick(msg[1]);
}
