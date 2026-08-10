SHELL = /bin/sh
NAME = codexion
SRC = src/codexion.c src/codexion_utils.c src/parser.c src/ft_atoi.c src/heap.c src/heap_utils.c \
		src/coder.c	src/coder_utils.c src/dongle.c src/monitor.c src/config.c src/codexion_utils2.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)
CC = cc
CPPFLAGS = -I ./src -MMD
CFLAGS = -Wall -Wextra -Werror -pthread
DBG = -fsanitize=address -g3
DBGT = -fsanitize=thread -g3


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
