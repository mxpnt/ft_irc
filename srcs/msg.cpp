#include "../incs/irc.hpp"

void	parsing_client_msg(char *str)
{
	SplitString	s(str);
	Commands	cmd(s);

	for (size_t i = 0; i < cmd.msg.size(); ++i)
		std::cout << i << " = "<< cmd.msg[i];
	
	int	found;

	found = msg[0].find("PASS ");
}
