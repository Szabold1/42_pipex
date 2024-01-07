NAME = pipex
CC = cc
RM = rm -f
SRCDIR = src
INCDIR = include
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -I$(LIBFTDIR)
LIBS = -L$(LIBFTDIR) -lft

SRC = pipex_utils.c \
		pipex.c

OBJ = $(SRC:%.c=$(SRCDIR)/%.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT): $(LIBFTDIR)
	cd $(LIBFTDIR) && $(MAKE)

all: $(NAME)

clean:
	cd $(LIBFTDIR) && $(MAKE) clean
	$(RM) $(OBJ)

fclean: clean
	cd $(LIBFTDIR) && $(MAKE) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
