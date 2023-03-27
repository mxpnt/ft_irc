#include "bot.hpp"

/***** CONSTRUCTORS AND DESTRUCTOR *****/

Bot::Bot()
{
}

Bot::Bot(std::string addr, long port, std::string pwd)
{
	this->server_addr = addr;
	this->port = port;
	this->password = pwd;

	this->user = "Bot";
	this->nick = "BotShady";
	this->realname = "Bot";

	this->isRegistered = 0;
}

Bot::Bot(Bot const &f)
{
	*this = f;
}

Bot::~Bot()
{
}

/***** OPERATORS *****/

Bot	&Bot::operator=(Bot const &rhs)
{
	this->server_addr = rhs.server_addr;
	this->port = rhs.port;
	this->password = rhs.password;

	this->user = rhs.user;
	this->nick = rhs.nick;
	this->realname = rhs.realname;
	this->pollfd = rhs.pollfd;
	this->addr = rhs.addr;

	this->isRegistered = rhs.isRegistered;

	return (*this);
}

/***** MEMBER FUNCTIONS *****/

void	Bot::sendMsg(std::string msg) const
{
	if (pollfd.revents & POLLOUT) {
		if (send(pollfd.fd, msg.c_str(), msg.size(), 0) < 0)
			perror("send()");
	}
}

size_t Bot::Recv(char* buffer, size_t size, int socket)
{
    size_t total = 0, n = 0;
    if ((n = recv(socket, buffer + total, size - total - 1, 0)) > 0)
        total += n;
    buffer[total] = 0;
    return (total);
}

void	Bot::launch()
{
	this->pollfd.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->pollfd.fd < 0)	{
		perror("socket()");
		exit(1);
	}
	this->addr.sin_family = AF_INET;
	this->addr.sin_port = htons(port);
	this->addr.sin_addr.s_addr = inet_addr(server_addr.c_str());
	pollfd.events = POLLIN | POLLOUT;
	if (fcntl(this->pollfd.fd, F_SETFL, O_NONBLOCK) < 0) {
		perror("fcntl()");
		exit(1);
	}
	connect(this->pollfd.fd, (struct sockaddr*)&addr, sizeof(addr));
}

void	Bot::run()
{
	while (1)
	{
		int	pollResult = poll(&pollfd, 1, 0);
		if (pollResult > 0)
		{
			if (!isRegistered && pollfd.revents & POLLOUT)
			{
				std::string	line;
				line = "USER " + user + " 0 * :" + realname + "\r\n";
				sendMsg(line);
				line = "NICK " + nick + "\r\n";
				sendMsg(line);
				line = "PASS " + password + "\r\n";
				sendMsg(line);
				this->isRegistered = 1;
			}
			else if (pollfd.revents & POLLIN)
			{
				char	buff[1024];
				int		n;
				n = Recv(buff, sizeof(buff), pollfd.fd);
				if (n == 0)
				{
					std::cerr << "Connection closed" << std::endl;
					break ;
				}
				else if  (n == -1)
				{
					perror("recv()");
					break ;
				}
				else
					message_manage(buff);
			}
		}
	}
}

void	Bot::message_manage(std::string msg)
{

	this->buffer.append(msg);
	if (buffer.find("\n") == std::string::npos)
		return ;

	std::string message = buffer.substr(0, buffer.size());
	std::string commandName = message.substr(message.find_first_of(" ") + 1);
	std::string commandArg;
	if (commandName.find(":") != std::string::npos)
		commandArg = commandName.substr(commandName.find_first_of(":") + 1);
	else
		commandArg = commandName.substr(commandName.find_first_of(" ") + 1);
	commandName = commandName.substr(0, commandName.find_first_of(" "));
	commandArg = commandArg.substr(0, commandArg.size() - 1);
	std::string commandSender = message.substr(1, message.find_first_of("!") - 1);
	
	if (commandName == "PRIVMSG")
	{
		std::string commandChan = "";

		if (buffer.find('#') != std::string::npos)
		{
			commandChan = buffer.substr(buffer.find('#'));
			commandChan = commandChan.substr(0, commandChan.find_first_of(" "));
		}
		if (commandChan != "")
			message = "PRIVMSG " + commandChan + " :" + randomMsg() + "\r\n";
		else
			message = "PRIVMSG " + commandSender + " :" + randomMsg() + "\r\n";
		sendMsg(message);
	}
	else if (commandName == "INVITE")
	{
		message = "JOIN " + commandArg + "\r\n";
		sendMsg(message);
		message = "PRIVMSG " + commandArg + " :" + randomMsg() + "\r\n";
		sendMsg(message);
	}
	this->buffer = "";
}

std::string	Bot::randomMsg()
{
	std::ifstream		ifs;
	std::stringstream	buf;
	std::string			bufStr;

	srand(time(NULL));
	ifs.open("ring.txt");
	if (ifs.fail())
	{
		ifs.close();
		return ("IFS OPEN FAILED RIP");
	}
	buf << ifs.rdbuf();
	ifs.close();
	bufStr = buf.str();
	std::vector<std::string> bufSplit = SplitString(bufStr).split("\r\n");
	size_t	bufLen = bufSplit.size();
	if (!bufLen)
		return ("NO RANDOM PHRASE FOR YOU");
	size_t	index = (rand() / 100) % bufLen;
	if (index == bufLen)
		index -= 1;
	return (bufSplit[index]);
}
