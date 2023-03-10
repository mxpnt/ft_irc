#include "../../incs/channelsClass.hpp"

Channels::Channels(std::string name, Client* oper)
{
    this->name = name;
    this->topic = "default topic";
    this->mode = 'p';
    user_list.push_back(oper);
}

Channels::~Channels()
{
    return ;
}

void    Channels::add_user(Client* user)
{
    this->user_list.push_back(user);
}

void    Channels::del_user(Client* user)
{
    std::vector<Client*>::iterator  it = this->user_list.begin();

    while (it != this->user_list.end())
    {
        if (*it == user)
            this->user_list.erase(it);
        it++;
    }
}

int Channels::is_oper(Client* user)
{
    if (user == this->user_list.front())
        return (1);
    return (0);
}

std::string Channels::getName() const
{
    return (this->name);
}

std::string Channels::getTopic() const
{
    return (this->topic);
}

std::vector<Client*>    Channels::getUserList() const
{
    return (this->user_list);
}

void    Channels::setTopic(std::string topic)
{
    this->topic = topic;
}

void    Channels::setMode(char mode)
{
    if (mode == 'p' || mode == 'i')
        this->mode = mode;
}
