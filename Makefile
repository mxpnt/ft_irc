NAME		=	ircserv

INC			=

SRCS		=	main.cpp \
				is_number.cpp \
				server.cpp \
				client.cpp \
				msg.cpp \
				splitstringClass.cpp

OBJS		=	${addprefix objs/, ${SRCS:.cpp=.o}}

CXX			=	clang++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

all:			${NAME}

objs/%.o:		%.cpp ${INC} Makefile
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