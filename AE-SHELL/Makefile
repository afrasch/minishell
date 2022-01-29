NAME = minishell
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
LIB_PATH = ./libft/
LIBS = -lreadline -L /Users/$$USER/.brew/opt/readline/lib -L ./libft -lft
INCLUDES = -I/Users/$$USER/.brew/opt/readline/include -I./includes


HEADERS_LIST =	minishell.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_DIR = ./src/
SRC_LIST =	main/main.c \
			parser/input1.c \
			parser/input2.c \
			parser/input3.c \
			parser/input4.c \
			parser/input5.c \
			error/err_free.c \
			init/initframe.c \
			init/lst_fct.c \
			helpers/helpers.c \
			execution/exec1.c \
			execution/exec2.c \
			execution/exec_utils.c \
			builtins/builtins1.c \
			builtins/builtin_helper.c \
			builtins/update_env.c \
			signals/signals1.c \
			vars/expansion.c \
			vars/variable_helper.c \

SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = ./obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(notdir $(OBJ_LIST)))

.PHONY : all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@make -C $(LIB_PATH) all
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJ) -o $(NAME)
	@echo "\033[0;33mCreate $(NAME)\033[m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "\033[0;33mCreate objects\033[m"

$(OBJ_DIR)%.o: $(SRC_DIR)*/%.c $(HEADERS)
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
