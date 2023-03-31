#include "../../incs/commandsClass.hpp"

void		Commands::cmd_kick(vector<Client*> &repertory, Client *client)
{
    if (this->msg.size() < 3)
    {
		client->numeric_reply("461", "need more params");
		return ;
    }

    Channel*	chan = find_channel(repertory[0]->channels, this->msg[1]);
	Client*		client_to_kick = find_client(repertory, this->msg[2]);
	string		str;
    if (!chan)
    {
        str = this->msg[1] + " :no such channel";
        client->numeric_reply("403", str);
    }
	else if (!client_to_invite)
	{
		str = this->msg[2] + " :No such nick/channel";
		client->numeric_reply("402", str);
	}
	else if (!chan->already_joined(client))
	{
		str = chan->getName() + " :not on channel";
		client->numeric_reply("442", str);
	}
	else if (!chan->is_oper(client))
	{
		str = chan->getName() + " :need to be an operator to kick";
		client->numeric_reply("482", str);
	}
	else if (!chan->already_joined(client_to_kick))
	{
		str = this->msg[2] + " " + chan->getName() + " :user not on channel";
		client->numeric_reply("441", str);
	}
	else
	{
		chan->multi_reply(client, "KICK", client_to_kick->getNick());
		chan->del_user(client_to_kick);
	}
}
