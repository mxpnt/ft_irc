#include "splitstringClass.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

SplitString::SplitString()
{
}

SplitString::SplitString(SplitString const &f)
{
	*this = f;
}

SplitString::SplitString(char *s): std::string(s)
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

std::vector<std::string>	&SplitString::split(char delim)
{
	if (!flds.empty())
			flds.clear();
	std::string	work = data();
	std::string	buf = "";
	size_t		i = 0;
	while (i < work.length())
	{
		if (work[i] != delim)
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
