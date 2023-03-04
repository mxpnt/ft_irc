#include "../../incs/commandsClass.hpp"

int	Commands::cmd_user(std::vector<Client*> &repertory, Client *client)
{
	(void) repertory;
	if (client->getUser() != "")
		std::cerr << "ERR_ALREADYREGISTERED" << std::endl;
	else
	{
		int	len = msg.size();
		if (len > 3)
		{
			if (msg[2] == "0" && msg[3] == "*")
			{
				client->setUser(msg[1]);
				if (len > 4)
				{
					if (msg[4][0] == ':')
					{
						std::string	realname;
						realname.append(msg[4]);
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
						/* choisir si ignorer apres 1 espace ou concatener */
						client->setRealname(msg[4]);
					}
				}
			}
		}
	}
	return (0);
}
