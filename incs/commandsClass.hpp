#ifndef COMMANDSCLASS_HPP
# define COMMANDSCLASS_HPP

# include "irc.hpp"

class	Commands {
private:
	std::string cmd[4];
	std::vector<std::string> msg;
public:
	Commands();
	Commands(Commands const &f);
	Commands(std::vector<std::string> vmsg);
	~Commands();

	Commands &operator=(Commands const &rhs);
};

#endif