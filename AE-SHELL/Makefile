NAME = minishell
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
LIB_PATH = ./libft/
LIBS = -lreadline -L /Users/$$USER/.brew/opt/readline/lib -L ./libft -lft
INCLUDES = -I/Users/$$USER/.brew/opt/readline/include


HEADERS_LIST =	minishell.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_DIR = ./src/
SRC_LIST =	main.c \
			input1.c \
			initframe.c \
			helpers.c \
			expansion.c \


SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = ./obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

.PHONY : all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@make -C $(LIB_PATH) all
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJ) -o $(NAME)
	@echo "\033[0;33mCreate $(NAME)\033[m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "\033[0;33mCreate objects\033[m"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean :
	@make -C $(LIB_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;31mRemove objects\033[m"

fclean : clean
	@make -C $(LIB_PATH) fclean
	@rm -f $(NAME)
	@echo "\033[0;31mRemove $(NAME)\033[m"

re : fclean all
