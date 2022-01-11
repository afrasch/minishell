#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
// 🌬⇨💨⚙️🎲⟹ AESHELL  🄰🄴 SHELL ❄️⚇▶️♾ ©️
// # define PROMPT		"<AE/SHELL> "
# define PROMPT		"\033[1;34m 𝔸𝔼𝕊ℍ𝔼𝕃𝕃 \033[m"
// # define PROMPT		"\033[1;34mAE\033[0;32m/\033[1;34mSHELL \033[0;32m~ \033[0;33m% \033[m"
# define ON 1
# define OFF 0


enum e_quote_status
{
	NO_Q,
	SINGLE_Q,
	DOUBLE_Q,
	META,
	PIPE,
	S_REDIR_L,
	S_REDIR_R,
	D_REDIR_L,//here_doc
	D_REDIR_R,

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
}	t_node;

/*cn = current node*/
typedef struct s_chunk
{
	int					type;
	int					quote_st;
	struct s_chunk		*next;
	struct s_chunk		*prev;
	t_node				*cn;
	t_node				*node_start;
}	t_chunk;

/*cc = current chunk*/
typedef struct s_frame
{
	t_var				*shell_env;
	t_var				*shell_env_start;
	int					in_fd;
	int					out_fd;
	int					exp_st;
	t_chunk				*cc;
	t_chunk				*chunk_start;
}	t_frame;

void	ft_lexer(char *str, t_frame *frame);
void	split_in_chunks(char *str, t_frame *frame);
void	init_frame(t_frame *frame);
void	next_node(t_frame *frame);
void	next_chunk(t_frame *frame);
void	add_letter(char c, t_frame *frame);
void	ft_print_stack(t_frame *frame);
void	print_var(t_frame *frame);
void	reset_frame(t_frame *frame);
void	ft_clear_nodes(t_node **current_node);
void	set_list_2start(t_frame *frame);
void	handle_quotes(t_frame *frame);
void	set_quote_state(char c, t_frame *frame);
void	expand(char *str, int *i, t_frame *frame);
int		is_alnum_uscore(char c);
int		expand_prequ(t_frame *frame, char cur_c, char next_c);
void	print_env(t_var *var);
void	add_exp_node(char c, char c_plus, t_frame *frame);
#endif