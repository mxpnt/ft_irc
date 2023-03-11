#include "../../incs/irc.hpp"

void register_process(std::vector<Client*> repertory, Client* client)
{
    std::string str;

    if (client->getRealname().empty() || !client->getNick().compare("*") || client->getServerPassword().empty())
        return ;
    std::cout << "starting registration..." << std::endl;
    if (client->getServerPassword().compare(repertory[0]->getServerPassword()))
    {
        client->numeric_reply("464", ":wrong password");
        throw std::exception();
    }
    str = ":Welcome to the " + (std::string)NETWORK_NAME + "Network, " + client->getNick();
    client->numeric_reply("001", str);

    str = ":Your host is " + (std::string)SERVER_NAME + "[" + repertory[0]->getIp() + "], running version " + (std::string)VERSION;
    client->numeric_reply("002", str);

    client->numeric_reply("003", ":this server was created today");

    str = (std::string)SERVER_NAME + " " + (std::string)VERSION + " ro ri"; //channel mode r=registered only, i=invite only
    client->numeric_reply("004", str);

    str = "CHANTYPES=# NETWORK=" + (std::string)NETWORK_NAME + " :supported by the server";
    client->numeric_reply("005", str);

    str = ":There are " + to_string(repertory.size() - 1) + " users and 0 invisible on 0 servers";
    client->numeric_reply("251", str);

    str = ":I have " + to_string(repertory.size() - 1) + " clients and 0 servers";
    client->numeric_reply("255", str);

    client->numeric_reply("221", "+r");
    client->numeric_reply("422", ":no message today");
    client->registered = 1;
}
