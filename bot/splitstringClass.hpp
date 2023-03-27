#ifndef SPLITSTRINGCLASS_HPP
# define SPLITSTRINGCLASS_HPP

# include "bot.hpp"

class	SplitString : public std::string	{
private:
	std::vector<std::string> flds;
public:
	SplitString();
	SplitString(SplitString const &f);
	SplitString(const std::string s);
	~SplitString();

	SplitString	&operator=(SplitString const &rhs);

	std::vector<std::string> &split(std::string delim);
};

#endif