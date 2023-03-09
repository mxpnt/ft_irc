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

void register_process(std::vector<Client*> repertory, Client* client, std::string server_password)
{
    std::string str;

    if (client->get_server_password_sent().compare(server_password))
    {
        client->numeric_reply("464", ":wrong password");
        throw std::exception();
    }
    str = ":Welcome to the " + (std::string)NETWORK_NAME + "Network, " + client->getNick();
    client->numeric_reply("001", str);

    str = ":Your host is " + (std::string)SERVER_NAME + "[" + (std::string)SERVER_IP + "/4545], running version " + (std::string)VERSION;
    client->numeric_reply("002", str);

    client->numeric_reply("003", ":this server was created today");

    str = (std::string)SERVER_NAME + " " + (std::string)VERSION + " r b"; //+ available user modes + available channel modes
    client->numeric_reply("004", str);

    str = "CHANTYPES=# NETWORK=" + (std::string)NETWORK_NAME + " :supported by the server";
    client->numeric_reply("005", str);

    str = ":There are " + to_string(repertory.size() - 1) + " users and 0 invisible on 0 servers";
    client->numeric_reply("251", str);

    str = ":I have " + to_string(repertory.size() - 1) + " clients and 0 servers";
    client->numeric_reply("255", str);

    client->numeric_reply("221", "+r");
    client->numeric_reply("422", ":no message today");
    client->set_registered(1);
}

//user mode: r->registered o-> operator

void command_manage(std::vector<Client*> repertory, int fd, char* buff, std::string server_password)
{
    Commands	c(buff);
    command_ptr f;
    Client      *author;
	
    author = find_client(repertory, fd);
    f = c.cmd_match();
    if (!author->get_registered() && !(f == &Commands::cmd_user || f == &Commands::cmd_nick || f == &Commands::cmd_pass))
	{
        author->numeric_reply("451", ":not registered");
        return ;
    }
    std::cout << buff;
	if (f)
        (c.*f)(repertory, author);
    if (!author->get_registered() && !author->getRealname().empty() && !author->getNick().empty() && !author->get_server_password_sent().empty())
        register_process(repertory, author, server_password);
}
