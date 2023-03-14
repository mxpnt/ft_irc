#include "../incs/irc.hpp"

int	main(int argc, char **argv)
{
	long			port;
	pair<int, string> server_socket_and_ip;

	if (argc != 3)	{
		cerr << "Wrong number of arguments" << endl;
		return (1);
	}
	port = strtol(argv[1], 0, 10);
	if (errno != 0 || port > 65535 || port < 0 || !is_number(argv[1])) {
		if (errno != 0)
			perror("strtol()");
		else
			cerr << "Port invalid" << endl;
		return (2);
	}
	server_socket_and_ip = create_server(port);
	server_socket_and_ip.second.append("/");
	server_socket_and_ip.second.append(to_string(port));
	wait_client(server_socket_and_ip, argv[2]);
	return (0);
}
