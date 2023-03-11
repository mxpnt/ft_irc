#include "../../incs/channelClass.hpp"

Channel::Channel(std::string name, Client* oper)
{
    this->name = name;
    this->topic = "default topic";
    this->mode = 'r';
    user_list.push_back(oper);
}

Channel::Channel(const Channel& x)
{
    *this = x;
}

Channel::~Channel()
{
    return ;
}

Channel&    Channel::operator=(const Channel& x)
{
    this->name = x.name;
    this->topic = x.topic;
    this->mode = x.mode;
    this->user_list = x.user_list;
    return (*this);
}

void    Channel::add_user(Client* user)
{
    this->user_list.push_back(user);
}

void    Channel::del_user(Client* user)
{
    std::vector<Client*>::iterator  it = this->user_list.begin();

    while (it != this->user_list.end())
    {
        if (*it == user)
            this->user_list.erase(it);
        it++;
    }
}

int Channel::is_oper(Client* user)
{
    if (user == this->user_list.front())
        return (1);
    return (0);
}

void    Channel::multi_reply(Client* sender, std::string cmd, std::string dst, std::string description)
{
    std::vector<Client*>::iterator  it = this->user_list.begin();

    while (it != this->user_list.end())
    {
        (*it)->reply(sender, cmd, dst, description);
        it++;
    }
}

std::string Channel::getName() const
{
    return (this->name);
}

std::string Channel::getTopic() const
{
    return (this->topic);
}

char    Channel::getMode() const
{
    return (this->mode);
}

std::string    Channel::getSymbol() const
{
    //= -> public, @ -> secret
    if (this->mode == 'r')
        return ("=");
    else
        return ("@");
}

std::string Channel::getUser() const
{
    std::vector<Client*>::const_iterator  it = this->user_list.begin();
    std::string user = "@";

    while (it != this->user_list.end())
    {
        user.append((*it)->getNick());
        user.append(" ");
        it++;
    }
    user.erase(user.size() - 1);
    return (user);
}

std::vector<Client*>    Channel::getUserList() const
{
    return (this->user_list);
}

void    Channel::setTopic(std::string topic)
{
    this->topic = topic;
}

void    Channel::setMode(char mode)
{
    if (mode == 'p' || mode == 'i')
        this->mode = mode;
}
