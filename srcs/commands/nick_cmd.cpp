#include "../../incs/commandsClass.hpp"

int	is_valid_nick(string nick)
{
	int	i = 0;

	while (nick[i])
	{
		if (nick[i] == '@' || nick[i] == '_' || nick[i] == '|'
		|| nick[i] == '\\' || nick[i] == '/')
			return (1);
		++i;
	}
	return (0);
}

void	Commands::cmd_nick(vector<Client*> &repertory, Client *client)
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
	vector<Client*>::iterator	it = repertory.begin();
	while (it != repertory.end())
	{
		if (msg[1] == (*it)->getNick())
		{
			client->numeric_reply("433", ":Nickname is already in use");
			return ;
		}
		++it;
	}
	if (client->registered)
		client->reply(client, "NICK", "", this->msg[1]);
	client->setNick(msg[1]);
}
