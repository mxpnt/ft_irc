#include "bot.hpp"

static int	is_number(std::string str)
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

int	main(int argc, char**argv)
{
	if (argc != 4)
	{
		std::cerr << "Wrong number of arguments. Please enter <server_addr> <port> <password>" << std::endl;
		return (1);
	}
	long port = strtol(argv[2], 0, 10);
	if (errno != 0 || port > 65535 || port < 0 || !is_number(argv[2])) {
		if (errno != 0)
			perror("strtol()");
		else
			std::cerr << "Port invalid" << std::endl;
		return (2);
	}
	Bot	bot(argv[1], port, argv[3]);

	bot.launch();
	bot.run();
	return (0);
}
