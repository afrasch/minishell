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
			main/utils_gnl.c \
			removethisfolder/helpers.c \
			parser/parser.c \
			parser/quotes.c \
			parser/set_flags.c \
			parser/input_check.c \
			parser/rearrange.c \
			parser/redirections.c \
			error/error.c \
			error/sig_error.c \
			error/check_invalid_input_1.c \
			error/check_invalid_input_2.c \
			init/initframe.c \
			lists/conversion.c \
			lists/deletion.c \
			lists/determination.c \
			lists/iteration.c \
			execution/exec_cmd.c \
			execution/execute.c \
			execution/childprocess.c \
			execution/get_access.c \
			execution/exec_utils.c \
			builtins/builtin_help_execute.c \
			builtins/exit.c \
			builtins/env.c \
			builtins/env_update.c \
			builtins/unset.c \
			builtins/export.c \
			builtins/pwd.c \
			builtins/cd.c \
			builtins/echo.c \
			signals/signals.c \
			signals/hd_signals.c \
			signals/signals_kill.c \
			heredoc/hd_name_generator.c \
			heredoc/hd_set_fd.c \
			heredoc/hd_expansion.c \
			heredoc/hd_execution.c \
			heredoc/hd_close.c \
			free/free_frame.c \
			free/free_nodes.c \
			variables/expansion.c \
			variables/expansion_helper.c \
			variables/environment.c \
			variables/environment_helper.c \

SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = ./obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(notdir $(OBJ_LIST)))

.PHONY : all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@make -C $(LIB_PATH) all
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBS) -o $(NAME)
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
