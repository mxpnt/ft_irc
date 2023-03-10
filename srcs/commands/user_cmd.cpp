#include "../../incs/commandsClass.hpp"

void	Commands::cmd_user(std::vector<Client*> &repertory, Client *client)
{
	(void) repertory;

	if (client->getUser() != "")
		client->numeric_reply("462", ":You may not reregister");
	else
	{
		int	len = msg.size();
		if (len > 3)
		{
			if (msg[2] == "0" && msg[3] == "*")
			{
				if (msg[1].length() > USERLEN - 1)
					msg[1].erase(USERLEN, std::string::npos);
				client->setUser(msg[1]);
				if (len > 4)
				{
					if (msg[4][0] == ':')
					{
						std::string	realname(msg[4]);
						for (int i = 5; i < len; ++i)
						{
							realname.append(" ");
							realname.append(msg[i]);
						}
						realname.erase(realname.begin());
						client->setRealname(realname);
					}
					else
					{
						client->setRealname(msg[4]);
					}
				}
			}
		}
		else
		{
			client->numeric_reply("461", ":Not enough parameters");
		}
	}
	return ;
}
