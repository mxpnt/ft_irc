#include "../incs/irc.hpp"

void command_manage(std::vector<Client*> repertory, int fd, char* buff)
{
    Commands	c(buff);
	command_ptr f;

    f = c.cmd_match();
}
