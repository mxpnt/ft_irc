#include "../../incs/commandsClass.hpp"

void	Commands::cmd_names(vector<Client*> &repertory, Client *client)
{
	vector<string>	channels; 
	if (this->msg.size() == 1)
		channels = create_chans_name_tab(repertory[0]->channels);
	else
		channels = (SplitString(this->msg[1]).split(","));

	string						str;
	vector<string>::iterator	it = channels.begin();
	while (it != channels.end())
	{
		Channel* chan = find_channel(repertory[0]->channels, (*it));

		if (!chan)
		{
			str = this->msg[1] + " :no such channel";
        	client->numeric_reply("403", str);
		}
		else if (chan->getMode() == 'i')
		{
			str = chan->getName() + " :End of NAMES list";
			client->numeric_reply("366", str);
		}
		else
		{
			str = chan->getSymbol() + " " + chan->getName() + " :" + chan->getUsers();
			client->numeric_reply("353", str);

			str = chan->getName() + " :End of NAMES list";
			client->numeric_reply("366", str);
		}
		it++;
	}
}
