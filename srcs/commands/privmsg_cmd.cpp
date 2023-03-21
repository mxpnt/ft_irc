#include "../../incs/commandsClass.hpp"

int	is_oper(string dest)
{
	if (dest[0] == '@')
		return (1);
	return (0);
}

void	Commands::cmd_privmsg(vector<Client*> &repertory, Client *client)
{
	if (msg.size() < 3)
	{
		client->numeric_reply("461", ":need more params");
		return ;
	}

	string						msg_to_be_sent = msg[2];
	vector<string>				dest = (SplitString(msg[1])).split(","); // Vector de tous les destinataires
	vector<string>::iterator	it_dest = dest.begin();
	while (it_dest != dest.end())
	{
		Channel	*rchan;
		Client	*rclient = find_client(repertory, (*it_dest));
		if (is_oper((*it_dest)))
		{
			(*it_dest).erase((*it_dest).begin());
			rchan = find_channel(repertory[0]->channels, (*it_dest));
			rclient = rchan->getUserList().front();
		}
		else
			rchan = find_channel(repertory[0]->channels, (*it_dest));

		if (rclient)
			rclient->reply(client, msg[0], rclient->getNick(), msg_to_be_sent);
		else if (rchan)
		{
			if (rchan->already_joined(client))
				rchan->multi_reply(client, msg[0], msg_to_be_sent);
			else
				client->numeric_reply("404", ":Cannot send to channel");
		}
		else
			client->numeric_reply("402", ":No such nick/channel");
		// str dans description
		++it_dest;
	}
}
