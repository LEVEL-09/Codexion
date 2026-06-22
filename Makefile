SHELL = /bin/sh
NAME = codexion.a
SRC = coders/codexion.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)
CC = cc
AR = ar rcs
CPPFLAGS = -I ./coders
CFLAGS = -Wall -Wextra -Werror -M
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
