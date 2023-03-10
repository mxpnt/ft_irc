#include "../../incs/irc.hpp"

Client* find_client(std::vector<Client*> &repertory, int fd)
{
    std::vector<Client*>::iterator it = repertory.begin();

    while(it != repertory.end())
    {
        if ((*it)->getFd() == fd)
            return ((*it));
        it++;
    }
    std::cerr << "error find_client: client not found" << std::endl;
    return (0);
}

//user mode: r->registered o-> operator

void command_manage(std::vector<Client*> repertory, int fd, char* buff)
{
    Commands	c(buff);
    command_ptr f = c.cmd_match();
    Client      *author = find_client(repertory, fd);
	
    if (!author->registered && !(f == &Commands::cmd_user || f == &Commands::cmd_nick || f == &Commands::cmd_pass))
	  {
        author->numeric_reply("451", ":not registered");
        return ;
    }
    std::cout << buff;
	if (f)
        (c.*f)(repertory, author);
    if (!author->registered)
        register_process(repertory, author);
}