# Makefile for Pipex

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)

# Target Binary
NAME = pipex
NAME_BONUS = $(NAME)_bonus

# File and Directory Management
RM = rm -f
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft_full.a
LIBS = -L$(LIBFT_DIR) -lft_full

# Source Directories
SRC_DIR = src
SRC_BONUS_DIR = src_bonus

# Source Files
SRC = errors.c \
		execute.c \
		file.c \
		path.c \
		pipex_utils.c \
		pipex.c

SRC_BONUS = errors_bonus.c \
			execute_bonus.c \
			file_bonus.c \
			path_bonus.c \
			pipex_bonus.c \
			pipex_utils_bonus.c

# Object Files
OBJ = $(SRC:%.c=$(SRC_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:%.c=$(SRC_BONUS_DIR)/%.o)

# Compilation Rules
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Target Rules
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

$(NAME_BONUS): $(LIBFT) $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(LIBS) -o $(NAME_BONUS)

# Library Compilation
$(LIBFT): $(LIBFT_DIR)
	cd $(LIBFT_DIR) && $(MAKE) full

# Phony Targets
all: $(NAME)

clean:
	cd $(LIBFT_DIR) && $(MAKE) clean
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	cd $(LIBFT_DIR) && $(MAKE) fclean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

bonus: $(NAME_BONUS)

.PHONY: all clean fclean re bonus
