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
    cerr << "error find_client: client not found" << endl;
    return (0);
}

void command_manage(vector<Client*> repertory, int fd, char* buff)
{
    size_t  i = 0;
    vector<string> cmds = SplitString(buff).split("\r\n");
	cout << cmds.size() << endl;
    while (i < cmds.size())
    {
        Commands	c(cmds[i]);
        command_ptr f = c.cmd_match();
        Client      *author = find_client(repertory, fd);
    
        if (!author->registered && !(f == &Commands::cmd_user || f == &Commands::cmd_nick || f == &Commands::cmd_pass))
	    {
            author->numeric_reply("451", ":not registered");
            return ;
        }
        cout << buff;
	    if (f)
            (c.*f)(repertory, author);
        if (!author->registered)
            register_process(repertory, author);
        i++;
    }
}