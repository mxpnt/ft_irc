NAME		=	ircserv

INC			=	incs/irc.hpp \
				incs/splitstringClass.hpp \
				incs/commandsClass.hpp \
				incs/clientClass.hpp \
				incs/channelClass.hpp

SRC			=	main.cpp

COMMANDS	=	command_manage.cpp \
				pass_cmd.cpp \
				user_cmd.cpp \
				nick_cmd.cpp \
				join_cmd.cpp \
				quit_cmd.cpp \
				invite_cmd.cpp \
				kick_cmd.cpp \
				mode_cmd.cpp \
				notice_cmd.cpp \
				ping_cmd.cpp \
				topic_cmd.cpp \
				privmsg_cmd.cpp \
				part_cmd.cpp \
				names_cmd.cpp \
				list_cmd.cpp

SERVER		= 	server.cpp \
				client.cpp \
				client_manage.cpp \
				register.cpp

CLASS		=	splitstringClass.cpp \
				commandsClass.cpp \
				clientClass.cpp \
				channelClass.cpp

UTILS		=	is_alphanum.cpp

SRCS		=	${SRC} \
				${addprefix commands/, ${COMMANDS}} \
				${addprefix server/, ${SERVER}} \
				${addprefix class/, ${CLASS}} \
				${addprefix utils/, ${UTILS}}

OBJS		=	${addprefix objs/, ${SRCS:.cpp=.o}}

CXX			=	c++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

all:			${NAME}

objs/%.o:		srcs/%.cpp ${INC} Makefile
				@mkdir -p ${dir $@}
				${CXX} ${CXXFLAGS} -c $< -o $@

${NAME}:		${OBJS} ${INC} Makefile
				${CXX} ${CXXFLAGS} -o ${NAME} ${OBJS}

clean:
				rm -rf objs/

fclean:			clean
				rm -rf ${NAME}

re :			fclean ${NAME}

.PHONY:			all clean fclean re