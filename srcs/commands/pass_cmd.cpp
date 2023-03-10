#include "../../incs/commandsClass.hpp"

void		Commands::cmd_pass(std::vector<Client*> &repertory, Client *client)
{
    (void) repertory;

    if (this->msg.size() < 2)
    {
        client->numeric_reply("461", ":need more parameters");
        return ;
    }
    if (client->getRegistered())
    {
        client->numeric_reply("462", ":already registered");
        return ;
    }
    client->setServerPasswordSent(this->msg[1]);
}
