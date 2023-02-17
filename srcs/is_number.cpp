#include "../incs/irc.hpp"

int	is_number(std::string str)
{
	int	i = 0;

	while (str[i])
	{
		if (!isdigit(str[i]))
			return (1);
		++i;
	}
	return (0);
}