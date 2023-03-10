#include "../../incs/irc.hpp"

int	is_valid_nick(std::string nick)
{
	int	i = 0;

	while (nick[i])
	{
		if (nick[i] == '@' || nick[i] == '_' || nick[i] == '|'
		|| nick[i] == '\\' || nick[i] == '/')
			return (1);
		++i;
	}
	return (0);
}
