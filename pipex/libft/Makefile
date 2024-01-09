NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# Directories
SRC_DIR = ./src
SRC_BONUS_DIR = $(SRC_DIR)/bonus
SRC_PRINTF_DIR = $(SRC_DIR)/ft_printf
SRC_GNL_DIR = $(SRC_DIR)/get_next_line

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
OBJ = $(SRC:%.c=$(SRC_DIR)/%.o)
SRC_BONUS = ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c
OBJ_BONUS = $(SRC_BONUS:%.c=$(SRC_BONUS_DIR)/%.o)
SRC_PRINTF = ft_printf_utils.c \
			ft_printf_utils2.c \
			ft_printf.c
OBJ_PRINTF = $(SRC_PRINTF:%.c=$(SRC_PRINTF_DIR)/%.o)
SRC_GNL = get_next_line_utils.c \
			get_next_line.c
OBJ_GNL = $(SRC_GNL:%.c=$(SRC_GNL_DIR)/%.o)

OBJ_FULL = $(OBJ) $(OBJ_BONUS) $(OBJ_PRINTF) $(OBJ_GNL)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_FULL)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(OBJ) $(OBJ_BONUS)
	$(AR) $(NAME) $(OBJ) $(OBJ_BONUS)

full: $(OBJ_FULL)
	$(AR) $(NAME) $(OBJ_FULL)
	
.PHONY: all clean fclean re bonus full