#include "../../incs/irc.hpp"

Client* find_client(vector<Client*> &repertory, int fd)
{
    vector<Client*>::iterator it = repertory.begin();

    while(it != repertory.end())
    {
        if ((*it)->getFd() == fd)
            return ((*it));
        it++;
    }
    return (0);
}

Client* find_client(vector<Client*> &repertory, string name)
{
	vector<Client*>::iterator it = repertory.begin();

    while(it != repertory.end())
    {
        if ((*it)->getNick() == name)
            return ((*it));
        it++;
    }
    return (0);
}

void	new_client(int server_socket, vector<struct pollfd> &tab_pollfd, vector<Client*> &repertory)
{
	struct sockaddr_in	client_addr;
	int					c_addr_len = sizeof(client_addr);
	int					client_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&c_addr_len);
	string			client_ip = inet_ntoa(client_addr.sin_addr);

	cout << "accept success " << client_ip << endl;
	repertory.push_back(new Client(tab_pollfd, client_socket, client_ip));
}

void    remove_from_chan(Client* client)
{
    while (!client->channels.empty())
    {
        string str = client->getNick() + " exited the network";
        client->channels.back()->del_user(client);
        client->channels.back()->multi_reply(client, "QUIT", str);
        client->channels.pop_back();
    }
    while (!client->invite_recv.empty())
    {
        client->invite_recv.back()->del_invite(client);
        client->invite_recv.pop_back();
    }
}

void	delete_client(vector<Client*>& repertory, int fd, int fd_good)
{
	vector<Client*>::iterator	it = repertory.begin();
	Client*	client = find_client(repertory, fd);

    if (fd_good)
        *client << ":" << SERVER_NAME << " ERROR : Connection closed\n";
    remove_from_chan(client);
	while (it != repertory.end())
	{
		if (*it == client)
		{
	        cout << client->getNick() << " disconnected" << endl;
			delete *it;
			repertory.erase(it);
			return ;
		}
		it++;
	}
}
