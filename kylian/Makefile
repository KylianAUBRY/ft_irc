NAME	=	ircserv

NAMEBOTE = botirc

SRCS	=	src/main.cpp \
			src/Server.cpp \
			src/User.cpp \
			src/Channel.cpp \
			src/CmdServer.cpp \
			src/mode.cpp \

SRCSBOTE 	=	bote/main.cpp \

OBJ =	${SRCS:.cpp=.o}

OBJBOTE =	${SRCSBOTE:.cpp=.o}

CC =	c++

CFLAGS	=	-Wall -Wextra -Werror -g -std=c++98

.c.o:
			$(CC) $(CFLAGS) -cpp $< -o $(<:.cpp=.o)

$(NAME): ${OBJ}
		$(CC) $(CFLAGS) -o $(NAME) ${OBJ}

$(NAMEBOTE): ${OBJBOTE}
		$(CC) $(CFLAGS) -o $(NAMEBOTE) ${OBJBOTE}

bote:	${NAMEBOTE}

all:	${NAME}

clean:
		rm -f ${OBJ} ${OBJBOTE}

fclean:	clean
		rm -f ${NAME} ${NAMEBOTE}

re:	fclean all

.PHONY: all clean fclean re