#include "../incs/irc.hpp"

void command_manage(std::vector<Client*> repertory, int fd, char* buff)
{
    Commands	c(buff);
	void (Commands::*f)(std::vector<Client*>,int);
	
    f = c.cmd_match(repertory, fd);
	f(repertory, fd);
}
