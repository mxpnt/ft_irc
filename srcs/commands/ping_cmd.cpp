#include "../../incs/commandsClass.hpp"

void		Commands::cmd_ping(vector<Client*> &repertory, Client *client)
{
    (void)  repertory;

    if (this->msg.size() < 2)
        client->numeric_reply("461", ":need more params");
    else if (!this->msg[0].compare("PING"))
        *client << ":" << SERVER_NAME << " PONG :" << this->msg[1] << "\n";
    else if (!this->msg[0].compare("PONG"))
        cout << "PONG :" << this->msg[1] << endl;
}
