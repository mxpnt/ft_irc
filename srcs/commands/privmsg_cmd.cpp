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

	string						str;
	vector<string>				dest = (SplitString(msg[1])).split(","); // Vector de tous les destinataires
	vector<string>::iterator	it_dest = dest.begin();
	Channel	*rchan;
	Client	*rclient; 
	while (it_dest != dest.end())
	{
		rclient = find_client(repertory, (*it_dest));
		if (is_oper((*it_dest)))
		{
			(*it_dest).erase((*it_dest).begin());
			rchan = find_channel(repertory[0]->channels, (*it_dest));
			if (rchan)
				rclient = rchan->getUserList().front();
		}
		else
			rchan = find_channel(repertory[0]->channels, (*it_dest));

		if (rclient)
			rclient->reply(client, msg[0], rclient->getNick(), msg[2]);
		else if (rchan)
		{
			if (rchan->already_joined(client))
				rchan->multi_privmsg_reply(client, msg[0], msg[2]);
			else
			{
				str = (*it_dest) + " :Cannot send to channel";
				client->numeric_reply("404", str);
			}
		}
		else
		{
			str = (*it_dest) + " :No such nick/channel";
			client->numeric_reply("402", str);
		}
		++it_dest;
	}
}
