#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define PROMPT		"SHELL~SHOCK "
// # define PROMPT		"\033[1;34mAE\033[0;32m/\033[1;34mSHELL \033[0;32m~ \033[0;33m% \033[m"
# define ON 1
# define OFF 0
# define ERROR -1

typedef enum e_builtin
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NONE,
} t_builtin;

enum e_quote_status
{
	NO_Q,
	SINGLE_Q,
	DOUBLE_Q,
};

enum e_operators
{
	PIPE,
	S_REDIR_L,
	S_REDIR_R,
	D_REDIR_L,//here_doc
	D_REDIR_R,
	WORD,
	// META,
};

typedef struct s_var
{
	char			*name;
	char			*con;
	struct s_var	*next;
}	t_var;

typedef struct s_node
{
	char				*content;
	int					type;
	int					quote_st;
	int					word;
	struct s_node		*next;
	struct s_node		*prev;
	char				typ[15];
}	t_node;

/*cn = current node*/
typedef struct s_chunk
{
	int					type;
	int					quote_st;
	struct s_chunk		*next;
	struct s_chunk		*prev;
	int					in_fd;
	int					out_fd;
	t_node				*cn;
	t_node				*node_start;
	int					cc_errno;
	char				**cmd_arr;
}	t_chunk;

/*cc = current chunk*/
typedef struct s_frame
{
	t_var				*shell_env;
	t_var				*shell_env_start;
	char				**original_env;
	int					exp_st;
	t_chunk				*cc;
	t_chunk				*chunk_start;
	char				**paths;
	int					saved_in_fd;
	int					saved_out_fd;
}	t_frame;

int			ft_lexer(char *str, t_frame *frame);
void		add_letter(char c, t_frame *frame);
void		split_in_chunks(char *str, t_frame *frame);
void		handle_quotes(t_frame *frame);
void		set_quote_state(char c, t_frame *frame);
void		expand(char *str, int *i, t_frame *frame);
int			expand_prequ(t_frame *frame, char cur_c, char next_c);
int			handle_meta_arrows(t_frame *frame);
int			check_for_redir(t_frame *frame);
void		get_path(t_frame *frame);
void		executer(t_frame *frame, char *cmd);
int			execute_function(t_frame *frame);
void		execute_builtin(t_frame *frame, char *cmd);

void		init_frame(t_frame *frame);
void		next_node(t_frame *frame);
void		next_chunk(t_frame *frame);
void		free_node(t_node *node);
void		init_node(t_frame *frame);
void		reset_frame(t_frame *frame);
void		ft_clear_nodes(t_node **current_node);
void		set_list_2start(t_frame *frame);
int			is_alnum_uscore(char c);
int			control_nodes_raw(t_frame *frame);
void		delete_node(t_frame	*frame, t_node *node);
char		**list_to_arr(t_node *node_start);
void		re_arrange_list(t_frame *frame);
t_builtin	check_for_builtin(char *input_cmd);
void		reset_fd(t_frame *frame);
void		print_env(t_var *var);



void		print_var(t_frame *frame);
void		ft_print_stack(t_frame *frame);
void		ft_print_stack_plain(t_frame *frame);
void		debug_print(t_frame *frame);
void		debug_print_full(t_frame *frame);
#endif