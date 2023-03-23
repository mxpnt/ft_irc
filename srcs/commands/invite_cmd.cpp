#include "../../incs/commandsClass.hpp"

void		Commands::cmd_invite(vector<Client*> &repertory, Client *client)
{
	if (this->msg.size() < 3)
    {
		client->numeric_reply("461", "need more params");
		return ;
    }

    Channel*	chan = find_channel(repertory[0]->channels, this->msg[2]);
	Client*		client_to_invite = find_client(repertory, this->msg[1]);
	string		str;
    if (!chan)
    {
        str = this->msg[2] + " :no such channel";
        client->numeric_reply("403", str);
    }
	else if (!chan->already_joined(client))
	{
		str = chan->getName() + " :not on channel";
		client->numeric_reply("442", str);
	}
	else if (!chan->is_oper(client))
	{
		str = chan->getName() + " :need to be an operator to invite";
		client->numeric_reply("482", str);
	}
	else if (chan->already_joined(client_to_invite))
	{
		str = chan->getName() + " " + this->msg[1] + " :user already on channel";
		client->numeric_reply("444", str);
	}
	else
	{
		chan->add_invite(client_to_invite);
		str = client_to_invite->getNick() + " " + chan->getName();
		client->numeric_reply("341", str);
		client_to_invite->reply(client, "INVITE", client_to_invite->getNick(), chan->getName());
	}
}
