#include "../../incs/commandsClass.hpp"

void	Commands::cmd_user(vector<Client*> &repertory, Client *client)
{
	(void) repertory;

	if (!client->getUser().empty())
	{
		client->numeric_reply("462", ":You may not reregister");
		return ;
	}

	if (this->msg.size() > 4 && ((this->msg[2] == "0" && this->msg[3] == "*") || (this->msg[2] == "*" && this->msg[3] == "0")))
	{
		if (this->msg[1].length() > USERLEN - 1)
			msg[1].erase(USERLEN, string::npos);
		client->setUser(this->msg[1]);
		client->setRealname(this->msg[4]);
	}
	else if (this->msg.size() <= 4)
		client->numeric_reply("461", ":Not enough parameters");
	return ;
}
