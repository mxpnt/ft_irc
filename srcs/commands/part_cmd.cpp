#include "../../incs/commandsClass.hpp"

void	Commands::cmd_part(vector<Client*> &repertory, Client *client)
{
	if (this->msg.size() < 2)
    {
        client->numeric_reply("461", "need more params");
        return ;
    }

	string			str;
	vector<string>	channels = (SplitString(this->msg[1]).split(","));
	vector<string>::iterator	it = channels.begin();
	while (it != channels.end())
	{
		Channel* chan = find_channel(repertory[0]->channels, (*it));

		if (!chan)
		{
			str = this->msg[1] + " :no such channel";
        	client->numeric_reply("403", str);
		}
		else if (!chan->already_joined(client))
		{
			str = chan->getName() + " :not on channel";
			client->numeric_reply("442", str);
		}
		else
		{
			str = client->getNick() + " is leaving the channel";
			chan->multi_reply(client, "PART", str);
			chan->del_user(client);
		}
		it++;
	}
}
