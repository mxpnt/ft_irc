#include "../incs/irc.hpp"

void command_manage(std::vector<Client*> repertory, int fd, char* buff)
{
    (void) repertory;
    (void) fd;
    Commands	c(buff);
	
    c.cmd_match();
}
