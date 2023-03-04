#include "../../incs/commandsClass.hpp"

void		Commands::cmd_pass(std::vector<Client*> &repertory, Client *client)
{
    (void) repertory;
    int fd = client->get_fd();

    if (this->msg.size() < 2)
    {
        write(fd, "FAIL PASS ERR_NEEDMOREPARAMS\n", 29);
        return ;
    }
    if (client->get_registered())
    {
        write(fd, "FAIL PASS ERR_ALREADYREGISTERED", 31);
        return ;
    }
    client->set_server_password_sent(this->msg[1]);
}
