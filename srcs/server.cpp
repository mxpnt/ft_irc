#include "../incs/irc.hpp"

int	create_server(int port, std::string password)
{
	int	listen_sd;
	int	bind_result;
	int	listen_result;
	int	rc;
	struct sockaddr_in server_addr;

	listen_sd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sd < 0) {
		perror("socket()");
		exit(-1);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// pas le droit a fcntl
	rc = fcntl(listen_sd, F_SETFL, O_NONBLOCK);
	if (rc < 0)
		perror("fcntl()");
	bind_result = bind(listen_sd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (bind_result < 0)
		perror("bind()");
	listen_result = listen(listen_sd, 5);
	if (listen_result < 0)
		perror("listen()");
	std::cout << "Server start" << std::endl;
	(void) password;
	return (listen_sd);
}

struct pollfd	poll_init(int server_socket)
{
	struct pollfd pollfds;

	pollfds.fd = server_socket;
	pollfds.events = POLLIN;
	return (pollfds);
}
