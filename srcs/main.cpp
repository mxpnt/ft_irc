#include "../incs/irc.hpp"

int	main(int argc, char **argv)
{
	int				server_socket;
	long			port;

	if (argc != 3)	{
		std::cerr << "Wrong number of arguments" << std::endl;
		return (1);
	}
	port = strtol(argv[1], 0, 10);
	if (errno != 0 || port > 65535 || port < 0 || is_number(argv[1])) {
		if (errno != 0)
			perror("strtol()");
		else
			std::cerr << "Port invalid" << std::endl;
		return (2);
	}
	server_socket = create_server(port);
	wait_client(server_socket, argv[2]);
	return (0);
}
