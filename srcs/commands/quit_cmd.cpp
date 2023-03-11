#include "../../incs/irc.hpp"

void	Commands::cmd_quit(vector<Client*> &repertory, Client *client)
{
	if (msg.size() > 1)
	{
		*client << ":" << client->getUser() << "@" << client->getIp() << " ERROR : Connection closed\n";
		// envoyer msg avec raison a tous les clients qui partagent un channel avec cet user
	}
	else
	{
		*client << ":" << (string)SERVER_NAME << " ERROR : Connection closed\n";
		// envoyer msg Quit: a tous les clients qui partagent un channel avec cet user
	}
	throw exception();
}
