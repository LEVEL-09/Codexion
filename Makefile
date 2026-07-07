SHELL = /bin/sh
NAME = codexion
SRC = src/codexion.c src/parser.c src/ft_atoi.c src/heap.c src/heap_utils.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)
CC = cc
CPPFLAGS = -I ./src -MMD
CFLAGS = -Wall -Wextra -Werror -pthread


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
