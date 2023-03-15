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

SplitString::SplitString(string str)
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

vector<string>	&SplitString::split(char delim)
{
	if (!flds.empty())
			flds.clear();
	string	work = data();
	string	buf = "";
	size_t		i = 0;
	while (i < work.length())
	{
		if (work[i] != delim && work[i] != '\r' && work[i] != '\n')
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
