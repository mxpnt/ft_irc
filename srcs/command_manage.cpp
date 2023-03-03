#include "../incs/irc.hpp"

Client* find_client(std::vector<Client*> &repertory, int fd)
{
    std::vector<Client*>::iterator it = repertory.begin();

    while(it != repertory.end())
    {
        if ((*it)->get_fd() == fd)
            return ((*it));
        it++;
    }
    std::cerr << "error find_client: client not found" << std::endl;
    return (0);
}

void command_manage(std::vector<Client*> repertory, int fd, char* buff)
{
    Commands	c(buff);
    command_ptr f;
    Client      *author;
	
    author = find_client(repertory, fd);
    f = c.cmd_match();
	std::cout << "OK\n";
	if (f)
    	(c.*f)(repertory, author);
	// std::cout << buff;
}
