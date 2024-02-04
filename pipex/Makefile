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
SRC = clean_up.c \
	  errors.c \
	  execute.c \
	  init_data.c \
	  main.c \
	  set_data_cmds.c \
	  set_data_files.c \
	  set_data.c

SRC_BONUS = b_clean_up.c \
			b_errors.c \
			b_execute.c \
			b_init_data.c \
			b_main.c \
			b_set_data_cmds.c \
			b_set_data_files.c \
			b_set_data.c

# Object Files
OBJ = $(SRC:%.c=$(SRC_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:%.c=$(SRC_BONUS_DIR)/%.o)

# Compilation Rules
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(SRC_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Target Rules
$(NAME): $(LIBFT) $(OBJ)
	@echo "🔨 compiling $(NAME)"
	@$(CC) $(OBJ) $(LIBS) -o $(NAME)
	@echo "✅ $(NAME) compiled"

$(NAME_BONUS): $(LIBFT) $(OBJ_BONUS)
	@echo "🔨 compiling $(NAME_BONUS)"
	@$(CC) $(OBJ_BONUS) $(LIBS) -o $(NAME_BONUS)
	@echo "✅ $(NAME_BONUS) compiled"

# Library Compilation
$(LIBFT): $(LIBFT_DIR)
	@echo "🔨 compiling libft"
	@cd $(LIBFT_DIR) && $(MAKE) full
	@echo "✅ libft compiled"

# Phony Targets
all: $(NAME)

clean:
	@cd $(LIBFT_DIR) && $(MAKE) clean
	@$(RM) $(OBJ) $(OBJ_BONUS)
	@echo "✅ object files removed"

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) fclean
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "✅ executables removed"

re: fclean all

bonus: $(NAME_BONUS)

rebonus: fclean bonus

.PHONY: all clean fclean re bonus
