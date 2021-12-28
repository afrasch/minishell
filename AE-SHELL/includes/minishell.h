#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define PROMPT		"AE/SHELL ~ % "

enum e_quote_status
{
	NO_Q,
	SINGLE_Q,
	DOUBLE_Q,
};

typedef struct s_node
{
	char				*content;
	int					type;
	int					quote_st;
	struct s_node		*next;
}	t_node;

typedef struct s_frame
{
	char	**shell_env;
	int		in_fd;
	int		out_fd;
	t_node	*current_node;
}	t_frame;


void	ft_lexer(char *str, t_frame *frame);
void	init_frame(t_frame *frame);
void	next_node(t_frame *frame);
void 	add_letter(char c, t_frame *frame);
#endif