#include "../../incs/channelClass.hpp"

Channel::Channel(string name, Client* oper)
{
    this->name = name;
    this->topic = "";
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
	if (!this->already_joined(user))
    	this->user_list.push_back(user);
}

void    Channel::del_user(Client* user)
{
    vector<Client*>::iterator  it = this->user_list.begin();

    while (it != this->user_list.end())
    {
        if (*it == user)
		{
            this->user_list.erase(it);
			return ;
		}
		it++;
    }
}

int Channel::is_oper(Client* user)
{
    if (user == this->user_list.front())
        return (1);
    return (0);
}

int Channel::already_joined(Client* user)
{
    vector<Client*>::iterator   it = this->user_list.begin();

    while (it != this->user_list.end())
    {
        if ((*it) == user)
            return (1);
        it++;
    }
    return (0);
}

int Channel::check_invite(Client* user)
{
    vector<Client*>::iterator   it = this->invite_list.begin();

    while (it != this->invite_list.end())
    {
        if ((*it) == user)
            return (1);
        it++;
    }
    return (0);
}

void    Channel::add_invite(Client* user)
{
	if (!this->check_invite(user))
    	this->invite_list.push_back(user);
}

void	Channel::del_invite(Client* user)
{
	vector<Client*>::iterator	it;

    it = this->invite_list.begin();
    while (it != this->invite_list.end())
    {
        if (*it == user)
		{
            this->invite_list.erase(it);
			return ;
		}
        it++;
    }
}

void    Channel::multi_reply(Client* sender, string cmd, string description)
{
    vector<Client*>::iterator  it = this->user_list.begin();

    while (it != this->user_list.end())
    {
		(*it)->reply(sender, cmd, this->getName(), description);
        it++;
    }
}

void    Channel::multi_privmsg_reply(Client* sender, string cmd, string description)
{
    vector<Client*>::iterator  it = this->user_list.begin();

    while (it != this->user_list.end())
    {
		if ((*it) != sender)
        	(*it)->reply(sender, cmd, this->getName(), description);
        it++;
    }
}

void    Channel::multi_serv_reply(string cmd, string description)
{
    vector<Client*>::iterator  it = this->user_list.begin();

    while (it != this->user_list.end())
    {
        *(*it) << ":" << SERVER_NAME << " " << cmd << " :" << description << "\n";
        it++;
    }
}

string Channel::getName() const
{
    return (this->name);
}

string Channel::getTopic() const
{
    return (this->topic);
}

char    Channel::getMode() const
{
    return (this->mode);
}

string    Channel::getSymbol() const
{
    //'r' = '=' -> public, 'i' = '@' -> secret
    if (this->mode == 'r')
        return ("=");
    else
        return ("@");
}

string Channel::getUsers() const
{
    vector<Client*>::const_iterator  it = this->user_list.begin();
    string user = "@";

    while (it != this->user_list.end())
    {
        user.append((*it)->getNick());
        user.append(" ");
        it++;
    }
    user.erase(user.size() - 1);
    return (user);
}

vector<Client*>    Channel::getUserList() const
{
    return (this->user_list);
}

int	Channel::getUserCount() const
{
	return (this->user_list.size());
}

void    Channel::setTopic(string topic)
{
    this->topic = topic;
}

void    Channel::setMode(char mode)
{
    if (mode == 'p' || mode == 'i')
        this->mode = mode;
}
