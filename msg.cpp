#include "irc.hpp"

void	parsing_client_msg(char *str)
{
	SplitString					s(str);
	std::vector<std::string>	msg = s.split(' ');

	for (size_t i = 0; i < msg.size(); ++i)
		std::cout << i << " = "<< msg[i];
}
