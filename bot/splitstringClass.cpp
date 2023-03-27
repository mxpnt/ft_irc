#include "splitstringClass.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

SplitString::SplitString()
{
}

SplitString::SplitString(SplitString const &f): std::string(f.c_str())
{
	*this = f;
}

SplitString::SplitString(const std::string s): std::string(s)
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


int	check_delim(std::string delim, char c)
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

std::vector<std::string>	&SplitString::split(std::string delim)
{
	if (!flds.empty())
			flds.clear();

	std::string	work = data();
	std::string	buf = "";
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
