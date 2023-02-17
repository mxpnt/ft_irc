#ifndef COMMANDSCLASS_HPP
# define COMMANDSCLASS_HPP

# include "irc.hpp"

class	Commands {
private:
	std::map<std::string, void (Commands::*)(std::vector<std::string>)>	cmd;
	std::vector<std::string>	msg;
	std::string					name;

	void	init_map();
public:
	Commands();
	Commands(Commands const &f);
	Commands(SplitString s);
	~Commands();

	Commands &operator=(Commands const &rhs);
};

#endif