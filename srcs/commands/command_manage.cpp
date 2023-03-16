#include "../../incs/irc.hpp"

void command_manage(vector<Client*> repertory, int fd, char* buff)
{
    size_t  i = 0;
    vector<string> cmds = SplitString(buff).split("\r\n");
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