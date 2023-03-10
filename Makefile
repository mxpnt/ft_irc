NAME		=	ircserv

INC			=	incs/irc.hpp \
				incs/splitstringClass.hpp \
				incs/commandsClass.hpp \
				incs/clientClass.hpp

SRC			=	main.cpp

COMMANDS	=	command_manage.cpp \
				pass_cmd.cpp \
				user_cmd.cpp \
				nick_cmd.cpp

SERVER		= 	server.cpp \
				client.cpp

CLASS		=	splitstringClass.cpp \
				commandsClass.cpp \
				clientClass.cpp

UTILS		=	is_number.cpp \
				is_valid_nick.cpp

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