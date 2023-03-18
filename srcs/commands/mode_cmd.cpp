#include "../../incs/commandsClass.hpp"

void	Commands::cmd_mode(vector<Client*> &repertory, Client *client)
{
    if (this->msg.size() < 2)
    {
        client->numeric_reply("461", "need more params");
        return ;
    }

    Channel*	chan = find_channel(repertory[0]->channels, this->msg[1]);
	string		str;
    if (!chan)
    {
        str = this->msg[1] + " :no such channel";
        client->numeric_reply("403", str);
    }
	else if (this->msg.size() == 2)
	{
		str = chan->getName() + " " + chan->getMode();
		client->numeric_reply("324", str);
	}
	else if (chan->is_oper(client))
	{
		if(this->msg[2] == "+r" || this->msg[1] == "-i")
		{
			chan->setMode('r');
			chan->multi_reply(client, "MODE", "-i+r");
		}
		if(this->msg[2] == "-r" || this->msg[1] == "+i")
		{
			chan->setMode('i');
			chan->multi_reply(client, "MODE", "-r+i");
		}
		else
			client->numeric_reply("501", ":unknow mode flag");
	}
	else
	{
		str = chan->getName() + " :need to be an operator to change the topic";
		client->numeric_reply("482", str);
	}
}
