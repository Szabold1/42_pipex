# Makefile for Pipex

# File and Directory Management
RM = rm -f
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft_full.a
LIBS = -L$(LIBFT_DIR) -lft_full

# Headers
HEADERS_DIR = ./include
HEADERS = $(HEADERS_DIR)/pipex.h

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(HEADERS_DIR)

# Target Binary
NAME = pipex
NAME_BONUS = $(NAME)_bonus

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

SRC_BONUS = clean_up_bonus.c \
			errors_bonus.c \
			execute_bonus.c \
			init_data_bonus.c \
			main_bonus.c \
			set_data_bonus.c \
			set_data_cmds_bonus.c \
			set_data_files_bonus.c

# Object Files
OBJ = $(SRC:%.c=$(SRC_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:%.c=$(SRC_BONUS_DIR)/%.o)

# Compilation Rules
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(SRC_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

# Phony Targets
all: $(NAME)

clean:
	@cd $(LIBFT_DIR) && $(MAKE) clean
	@$(RM) $(OBJ) $(OBJ_BONUS)
	@echo "✅ object files removed"

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) fclean
	@echo "✅ libft library removed"
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "✅ executables removed"

re: fclean all

bonus: $(NAME_BONUS)

rebonus: fclean bonus

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
	@echo "🔨 creating libft"
	@cd $(LIBFT_DIR) && $(MAKE) full
	@echo "✅ libft created"

.PHONY: all clean fclean re bonus rebonus
