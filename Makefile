SHELL = /bin/sh
NAME = codexion.a
SRC = src/codexion.c src/parser.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)
CC = cc
AR = ar rcs
CPPFLAGS = -I ./src -MMD
CFLAGS = -Wall -Wextra -Werror -pthread 
RM = rm -f

-include $(DEP)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
