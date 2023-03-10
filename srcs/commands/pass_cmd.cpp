#include "../../incs/commandsClass.hpp"

void		Commands::cmd_pass(std::vector<Client*> &repertory, Client *client)
{
    (void) repertory;

    if (this->msg.size() < 2)
    {
        client->numeric_reply("461", ":need more parameters");
        return ;
    }
    if (client->registered)
    {
        client->numeric_reply("462", ":already registered");
        return ;
    }
    client->setServerPassword(this->msg[1]);
}
