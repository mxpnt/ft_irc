NAME		=	ircserv

INC			=	incs/irc.hpp \
				incs/splitstringClass.hpp \
				incs/commandsClass.hpp

SRC			=	main.cpp \
				is_number.cpp \
				server.cpp \
				client.cpp \
				splitstringClass.cpp \
				commandsClass.cpp

OBJS		=	${addprefix objs/, ${SRC:.cpp=.o}}

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