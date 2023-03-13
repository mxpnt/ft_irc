# include "../../incs/commandsClass.hpp"

Channel* find_channel(vector<Channel>& channels, string name)
{
    vector<Channel>::iterator  it = channels.begin();

    while (it != channels.end())
    {
        if (!(*it).getName().compare(name))
            return (&(*it));
        it++;
    }
    return (0);
}

void    Commands::cmd_join(vector<Client*> &repertory, Client *client)
{
    if (this->msg.size() < 2)
    {
        client->numeric_reply("461", ":need more params");
        return ;
    }
 
    string chan_name = this->msg[1];
    if (this->msg.size() > 2 || chan_name.at(0) != '#' || !is_alpha(&(chan_name[1])))
    {
        client->numeric_reply("476", ":bad chan name, only letters prefixed by a #");
        return ;
    }

    Channel* chan = find_channel(repertory[0]->channels, chan_name);
    if (chan == 0)
    {
        repertory[0]->channels.push_back(Channel(chan_name, client));
        chan = &repertory[0]->channels.back();
    }
    else if (chan->already_joined(client))
        return ;
    else if (chan->getMode() == 'i' && !chan->check_invite(client))
    {
        client->numeric_reply("473", ":invite only chan");
        return;
    }
    else
        chan->add_user(client);

    chan->multi_reply(client, "JOIN", chan_name, "joined channel");
    
    string str;
    str = chan->getName() + " :" + chan->getTopic();
    client->numeric_reply("332", str);
    
    str = chan->getSymbol() + " " + chan->getName() + " :" + chan->getUsers();
    client->numeric_reply("353", str);
    
    str = chan->getName() + " :End of NAMES list";
    client->numeric_reply("366", str);
}
