# include "../../incs/commandsClass.hpp"

void    Commands::cmd_join(std::vector<Client*> &repertory, Client *client)
{
    (void) repertory;

    if (this->msg.size() < 2)
        client->numeric_reply("461", ":need more params");
    if (this->msg.size() > 2 || this->msg[1].at(0) != '#' || !is_alpha(&(this->msg[1][1])))
        client->numeric_reply("476", ":bad chan name, only letters allowed prefixed by #");
}
