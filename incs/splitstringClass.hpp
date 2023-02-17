#ifndef SPLITSTRINGCLASS_HPP
# define SPLITSTRINGCLASS_HPP

# include "irc.hpp"

class	SplitString : public std::string	{
private:
	std::vector<std::string> flds;
public:
	SplitString();
	SplitString(SplitString const &f);
	SplitString(const char *s);
	~SplitString();

	SplitString	&operator=(SplitString const &rhs);

	std::vector<std::string> &split(char delim);
};

#endif