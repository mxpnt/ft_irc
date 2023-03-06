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

void register_process(Client* client, std::string server_password)
{
    std::string str;

    if (client->get_server_password_sent().compare(server_password))
    {
        client->numeric_reply("464", ":wrong password");
        *client << "ERROR :wrong password\n";
        throw std::exception();
    }
    *client << client->getRealname() << " :Welcome to the 42 Network, " << client->getNick() << "\n";
}

void command_manage(std::vector<Client*> repertory, int fd, char* buff, std::string server_password)
{
    Commands	c(buff);
    command_ptr f;
    Client      *author;
	
    author = find_client(repertory, fd);
    f = c.cmd_match();
    if (!author->get_registered() && !(f == &Commands::cmd_user || f == &Commands::cmd_nick || f == &Commands::cmd_pass))
	{
        write(fd, "FAIL * NEED_REGISTRATION :You need to be registered to continue\n", 64);
        return ;
    }
    //std::cout << buff;
	if (f)
        (c.*f)(repertory, author);
    if (!author->getRealname().empty() && !author->getNick().empty() && !author->get_server_password_sent().empty())
        register_process(author, server_password);
}
