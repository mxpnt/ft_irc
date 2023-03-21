#include "../../incs/commandsClass.hpp"

int	is_oper(string dest)
{
	if (dest[0] == '@')
		return (1);
	return (0);
}

void	Commands::cmd_privmsg(vector<Client*> &repertory, Client *client)
{
	vector<Channel*>	chan = client->channels;
	string			msg_to_be_sent;

	if (msg.size() < 3)
	{
		client->numeric_reply("461", ":need more params");
		return ;
	}
	SplitString		dest(msg[1].c_str()); // c_str() garantee NULL char
	vector<string>	vDest = dest.split(","); // Vector de tous les destinataires

	msg_to_be_sent = msg[2];
	vector<string>::iterator	it_dest = vDest.begin();
	while (it_dest != vDest.end())
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
