# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 19:26:57 by mlangloi          #+#    #+#              #
#    Updated: 2023/10/24 19:26:58 by mlangloi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			ircserv

CC = 			c++
CFLAGS = 		-Wall -Werror -Wextra -std=c++98 -g
LIBRARIES =
CFLAG = 		-c
OFLAG =			-o
IFLAG =			-I

MAKE = 			make -s -C
MAKE_CLEAN = 	make clean -s -C
MAKE_FCLEAN = 	make fclean -s -C

MKDIR =			mkdir -p
CP =			cp
RM =			rm -rf

SOURCES_DIR =	./src
OBJECTS_DIR =	./objs
HEADERS_DIR =	./include

FILES =		main.cpp \
			Server.cpp \
			User.cpp \

SRCS =			$(foreach FILE, $(FILES), $(shell find $(SOURCES_DIR) -name $(FILE)))

OBJS =			$(patsubst $(SOURCES_DIR)/%, $(OBJECTS_DIR)/%, $(SRCS:.cpp=.o))

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(IFLAG) $(HEADERS_DIR) $(CFLAG) $(OFLAG) $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBRARIES) $(OFLAG) $(NAME)

clean:
	@$(RM) $(OBJECTS_DIR)

fclean: clean
	@$(RM) $(NAME)

run: re
	./$(NAME) 3000 password

re: fclean all clean

.PHONY: all clean fclean re
