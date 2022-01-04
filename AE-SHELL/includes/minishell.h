#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define PROMPT		"\033[1;34mAE\033[0;32m/\033[1;34mSHELL \033[0;32m~ \033[0;33m% \033[m"
// # define PIPE	'|'


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
	int					general_st;
	struct s_node		*next;
	struct s_node		*prev;
}	t_node;

/*cn = current node*/
typedef struct s_chunk
{
	char				*content;
	int					type;
	int					quote_st;
	int					general_st;
	struct s_chunk		*next;
	struct s_chunk		*prev;
	t_node				*cn;
	t_node				*node_start;
}	t_chunk;

/*cc = current chunk*/
typedef struct s_frame
{
	char				**shell_env;
	int					in_fd;
	int					out_fd;
	t_chunk				*cc;
	t_chunk				*chunk_start;
}	t_frame;

void	ft_lexer(char *str, t_frame *frame);
void	init_frame(t_frame *frame);
void	next_node(t_frame *frame);
void	next_chunk(t_frame *frame);
void	add_letter(char c, t_frame *frame);
void	ft_print_stack(t_frame *frame);
void	reset_frame(t_frame *frame);
void	ft_clear_nodes(t_node **current_node);
void	set_list_2start(t_frame *frame);
void	handle_quotes(t_frame *frame);
void	set_quote_state(char c, t_frame *frame);
#endif