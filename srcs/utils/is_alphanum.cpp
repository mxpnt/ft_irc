#include "../../incs/irc.hpp"

int	is_number(string str)
{
	int	i = 0;

	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

int	is_alpha(string str)
{
	int	i = 0;

	while (str[i])
	{
		if (!isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_alphanum(string str)
{
	if(is_alpha(str) && is_number(str))
		return (1);
	return (0);
}
