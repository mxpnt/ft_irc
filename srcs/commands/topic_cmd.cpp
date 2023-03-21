#include "../../incs/commandsClass.hpp"

void		Commands::cmd_topic(vector<Client*> &repertory, Client *client)
{
    if (this->msg.size() < 2)
    {
        client->numeric_reply("461", "need more params");
        return ;
    }

    string  str;
    Channel* chan = find_channel(repertory[0]->channels, this->msg[1]);
    if (!chan)
    {
		str = this->msg[1] + " :no such channel";
        client->numeric_reply("403", str);
        return ;
    }
    if (!chan->already_joined(client))
    {
		str = chan->getName() + " :not on channel";
        client->numeric_reply("442", str);
        return ;
    }

    if (this->msg.size() == 2)
    {
        if (chan->getTopic().empty())
        {
            str = chan->getName() + " :no topic set";
            client->numeric_reply("331", str);
        }
		else
		{
			str = chan->getName() + " :" + chan->getTopic();
			client->numeric_reply("332", str);
		}
    }
	else
	{
		if (chan->is_oper(client))
		{
			chan->setTopic(this->msg[2]);
			chan->multi_serv_reply("TOPIC", chan->getTopic());
		}
		else
		{
			str = chan->getName() + " :need to be an operator to change the topic";
			client->numeric_reply("482", str);
		}
	}
}
