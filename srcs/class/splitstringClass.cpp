#include "../../incs/splitstringClass.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

SplitString::SplitString()
{
}

SplitString::SplitString(SplitString const &f): string(f.c_str())
{
	*this = f;
}

SplitString::SplitString(const char *s): string(s)
{
}

SplitString::~SplitString()
{
}

/***** OPERATORS *****/

SplitString	&SplitString::operator=(SplitString const &rhs)
{
	this->flds = rhs.flds;
	return (*this);
}

/***** MEMBER FUNCTIONS *****/

int	check_delim(string delim, char c)
{
	size_t	i = 0;

	while (i < delim.size())
	{
		if (delim[i] == c)
			return (0);
		i++;
	}
	return (1);
}

vector<string>	&SplitString::split(string delim)
{
	if (!flds.empty())
			flds.clear();

	string	work = data();
	string	buf = "";
	size_t		i = 0;

	while (i < work.length())
	{
		if (check_delim(delim, work[i]))
			buf += work[i];
		else if (buf.length() > 0)
		{
			flds.push_back(buf);
			buf = "";
		}
		++i;
	}
	if (!buf.empty())
		flds.push_back(buf);
	return (flds);
}

vector<string>	&SplitString::cmd_split(string delim)
{
	if (!flds.empty())
			flds.clear();

	string	work = data();
	string	buf = "";
	size_t		i = 0;
	int			x = 1;

	while (i < work.length())
	{
		if (x && work[i] == ':')
		{
			i++;
			delim = "";
			x = 0;
			continue ;
		}
		if (check_delim(delim, work[i]))
			buf += work[i];
		else if (buf.length() > 0)
		{
			flds.push_back(buf);
			buf = "";
		}
		++i;
	}
	if (!buf.empty())
		flds.push_back(buf);
	return (flds);
}
