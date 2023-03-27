#include "../../incs/irc.hpp"


void command_manage(vector<Client*> repertory, int fd, string buff)
{
    Client      *author = find_client(repertory, fd);
    author->buff.append(buff);
    if (buff.find("\n") == string::npos)
        return ;

    size_t  i = 0;
    vector<string> cmds = SplitString(author->buff).split("\r\n");
    while (i < cmds.size())
    {
        Commands	c(cmds[i]);
        command_ptr f = c.cmd_match();
    
        cout << author->buff;
        author->buff = "";
        if (!author->registered && !(!f || f == &Commands::cmd_user || f == &Commands::cmd_nick || f == &Commands::cmd_pass))
	    {
            author->numeric_reply("451", ":not registered");
            return ;
        }
	    if (f)
            (c.*f)(repertory, author);
        if (!author->registered)
            register_process(repertory, author);
        i++;
    }
}