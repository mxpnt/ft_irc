#include "../../incs/commandsClass.hpp"

void	Commands::cmd_privmsg(vector<Client*> &repertory, Client *client)
{
	vector<Channel*>	chan = client->channels;
	string			msg_to_be_sent;

	if (msg.size() > 1)
	{
		SplitString		dest(msg[1].c_str()); // c_str() garantee NULL char
		vector<string>	vDest = dest.split(","); // Vector de tous les destinataires

		if (msg.size() > 2)
		{
			msg_to_be_sent = msg[2];
			for (size_t i = 3; i < msg.size(); ++i)
			{
				msg_to_be_sent.append(" ");
				msg_to_be_sent.append(msg[i]);
			}
			msg_to_be_sent.erase(msg_to_be_sent.begin()); // Erase ':'
		}
		vector<string>::iterator	it_dest = vDest.begin();
		// Gérer les préfix '@', '+', ... ?
		while (it_dest != vDest.end())
		{
			vector<Client*>::iterator	it_rep = repertory.begin();
			int	find = 0;
			while (it_rep != repertory.end())
			{
				if ((*it_dest) == (*it_rep)->getNick())
				{
					// Envoyer msg
					(*it_rep)->reply(client, "PRIVMSG", (*it_rep)->getNick(), msg_to_be_sent);
					find = 1;
					break ;
				}
				++it_rep;
			}
			if (!find)
			{
				vector<Channel*>::iterator	it_chan = repertory[0]->channels.begin();
				while (it_chan != repertory[0]->channels.end())
				{
					if ((*it_dest) == (*it_chan)->getName())
					{
						// Envoyer msg
						(*it_chan)->multi_reply(client, "PRIVMSG", msg_to_be_sent);
						find = 1;
						break ;
					}
					++it_chan;
				}
				// Faire qqchose si pas trouvé ?
				if (!find)
				{
					// Nouvelle fonction numeric_reply <client> <nickname/channel> ... ?
					client->numeric_reply("402", ":No such nick/channel");
				}
			}
			++it_dest;
		}
	}
}
