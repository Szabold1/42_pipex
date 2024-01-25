# Library name
NAME = libft.a

# Source directories
SRC_DIR = ./src
SRC_BONUS_DIR = $(SRC_DIR)/bonus
SRC_GNL_DIR = $(SRC_DIR)/get_next_line
SRC_PRINTF_DIR = $(SRC_DIR)/ft_printf

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Archiver
AR = ar rcs

# Remove command
RM = rm -f

# Source files
SRC = ft_atoi.c \
      ft_bzero.c \
      ft_calloc.c \
      ft_isalnum.c \
      ft_isalpha.c \
      ft_isascii.c \
      ft_isdigit.c \
      ft_isprint.c \
      ft_itoa.c \
      ft_memchr.c \
      ft_memcmp.c \
      ft_memcpy.c \
      ft_memmove.c \
      ft_memset.c \
      ft_putchar_fd.c \
      ft_putendl_fd.c \
      ft_putnbr_fd.c \
      ft_putstr_fd.c \
      ft_split.c \
      ft_strchr.c \
      ft_strdup.c \
      ft_striteri.c \
      ft_strjoin.c \
      ft_strlcat.c \
      ft_strlcpy.c \
      ft_strlen.c \
      ft_strmapi.c \
      ft_strncmp.c \
      ft_strnstr.c \
      ft_strrchr.c \
      ft_strtrim.c \
      ft_substr.c \
      ft_tolower.c \
      ft_toupper.c

SRC_BONUS = ft_lstadd_back.c \
             ft_lstadd_front.c \
             ft_lstclear.c \
             ft_lstdelone.c \
             ft_lstiter.c \
             ft_lstlast.c \
             ft_lstmap.c \
             ft_lstnew.c \
             ft_lstsize.c

SRC_GNL = get_next_line_utils.c \
          get_next_line.c

SRC_PRINTF = ft_printf_utils.c \
            ft_printf_utils2.c \
            ft_printf.c

# Object files
OBJ = $(SRC:%.c=$(SRC_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:%.c=$(SRC_BONUS_DIR)/%.o)
OBJ_GNL = $(SRC_GNL:%.c=$(SRC_GNL_DIR)/%.o)
OBJ_PRINTF = $(SRC_PRINTF:%.c=$(SRC_PRINTF_DIR)/%.o)

# Default target
all: $(NAME)

# Build library
$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

# Compile individual source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	$(RM) $(OBJ) $(OBJ_BONUS) $(OBJ_GNL) $(OBJ_PRINTF)

# Remove all generated files
fclean: clean
	$(RM) $(NAME)

# Clean and build again
re: fclean all

# Build bonus part of the library
bonus: all $(OBJ_BONUS)
	$(AR) $(NAME) $(OBJ_BONUS)

# Build everything (bonus, get_next_line, ft_printf)
every: bonus $(OBJ_GNL) $(OBJ_PRINTF)
	$(AR) $(NAME) $(OBJ_BONUS) $(OBJ_GNL) $(OBJ_PRINTF)

# Declare phony targets
.PHONY: all clean fclean re bonus every
