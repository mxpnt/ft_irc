#include "../../incs/commandsClass.hpp"

void	Commands::cmd_nick(std::vector<Client*> &repertory, Client *client)
{
	(void) repertory;
	int fd =client->get_fd();
	std::string	str;
	
	if (msg.size() < 2)
	{
		std::cerr << "ERR_NONICKNAMEGIVEN" << std::endl;
		return ;
	}
	/* CHECK SI NICK DEJA UTILISE */
	if (msg[0] == "NICK" && msg[1] == "DEJA UTILISE")
	{
		std::cerr << "ERR_NICKNAMEINUSE" << std::endl;
		return ;
	}
	str = *client + (std::string)" NICK " + this->msg[1] + (std::string)"\n"; 
	write(fd, str.c_str(), str.size());
	client->setNick(msg[1]);
}
