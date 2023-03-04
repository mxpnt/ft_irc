#include "../../incs/irc.hpp"

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

int command_manage(std::vector<Client*> repertory, int fd, char* buff, std::string server_password)
{
    Commands	c(buff, server_password);
    command_ptr f;
    Client      *author;
    int         code_error = 0;
	
    author = find_client(repertory, fd);
    f = c.cmd_match();
	std::cout << buff;
	if (f)
    	code_error = (c.*f)(repertory, author);
    return (code_error);
}
