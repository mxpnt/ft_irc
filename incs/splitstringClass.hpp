#ifndef SPLITSTRINGCLASS_HPP
# define SPLITSTRINGCLASS_HPP

# include "irc.hpp"

class	SplitString : public string	{
private:
	vector<string> flds;
public:
	SplitString();
	SplitString(SplitString const &f);
	SplitString(const char *s);
	SplitString(string str);
	~SplitString();

	SplitString	&operator=(SplitString const &rhs);

	vector<string> &split(char delim);
};

#endif