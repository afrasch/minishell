#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <termios.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define PROMPT		"|SHELL~SHOCK| "
// # define PROMPT		"\033[1;34mAE\033[0;32m/\033[1;34mSHELL \033[0;32m~ \033[0;33m% \033[m"
# define ON 1
# define OFF 0
# define SHOW 3
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define PIPEIN -4
# define PIPEOUT -5
# define NO_PIPE -6

int		global;
typedef enum e_builtin
{
	B_ECHO,
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
	PIPED,
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
	int				just_export;
	struct s_var	*next;
}	t_var;

typedef struct s_hd_list
{
	char				*name_of_hd;
	struct s_hd_list	*next;
}	t_hd_list;

typedef struct s_node
{
	char				*content;
	int					type;
	int					handle_quote;
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
	t_builtin			built_in;
	struct s_chunk		*next;
	struct s_chunk		*prev;
	int					in_fd;
	int					out_fd;
	t_node				*cn;
	t_node				*node_start;
	int					cc_errno;
	char				**cmd_arr;
	int					hd_bool;
	char				*hd_path;
	int					expanded;
}	t_chunk;

/*cc = current chunk*/
typedef struct s_frame
{
	t_var				*shell_env;
	t_var				*shell_env_start;
	int					exp_st;
	t_chunk				*cc;
	t_chunk				*chunk_start;
	char				**paths;
	int					saved_in_fd;
	int					saved_out_fd;
	int					single_com;
	int					nl;
	t_hd_list			*hd_list;
	int					e_status;
}	t_frame;

typedef struct s_exec
{
	int	fd[2];
	int	tmp_fd;
}	t_exec;

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
int 		execute_function(t_frame *frame, t_exec *exec);
void		execute_builtin(t_frame *frame, char *cmd);

void		init_frame(t_frame *frame);
void		next_node(t_frame *frame);
void		next_chunk(t_frame *frame);
void		free_node(t_node *node);
void		init_node(t_frame *frame);
void		ft_clear_nodes(t_node **current_node);
void		set_list_2start(t_frame *frame);
void		add_var_node(t_frame *frame, char *name, char *content, int just_export);
int			is_alnum_uscore(char c);
int			control_nodes_raw(t_frame *frame);
void		delete_node(t_frame	*frame, t_node *node);
void		delete_var_node(t_frame	*frame, t_var *node);
char		**list_to_arr(t_node *node_start);
char		**env_list_to_arr(t_frame *frame);
void		re_arrange_list(t_frame *frame);
t_builtin	check_for_builtin(char *input_cmd, t_frame *frame);
void		reset_fd(t_frame *frame, int pipe_state);
void		print_env(t_var *var);
char		*ft_quote(char *str);
char		*ft_unquote(char *str);
void		set_quote_state_for_handle(char c, t_frame *frame);
char		*get_env_var(t_frame *frame, char *name);
int			look_for_var(t_frame *frame, char *name);
void		update_env(t_frame *frame, char *name, char *content, char *oldpwd);
void		split_env(char *str, t_frame *frame);

void		print_var(t_frame *frame);
void		ft_print_stack(t_frame *frame);
void		ft_print_stack_plain(t_frame *frame);
void		debug_print(t_frame *frame);
void		debug_print_full(t_frame *frame);
void 		print_hd_list(t_frame *frame);
char		*change_caps(char *input_cmd);

char 		*init_signals_and_prompt(t_frame *frame);
void		child_killer(int signal);
void		clear_signals();
//void		signals_for_child(t_frame *frame, int pid);
//void		switch_signal_print(int i, t_frame *frame);

int			ft_fork();
void		init_exec(t_exec *exec);
void		check_for_pipe(t_frame *frame);
int			get_access(t_frame *frame, char	*cmd);
void		execute_cmd(t_frame *frame, int i, char* cmd);
void		prepare_builtin_alone(t_frame *frame);
void		set_back_builtin_alone(t_frame *frame);

void		exit_minishell(t_frame *frame);
void		env(t_frame *frame);

char 		*create_rand_name();
int			do_here_doc(t_frame *frame);
char		*get_heredoc_prompt();
void		add_to_hd_list(t_frame *frame, char *path);
int			solve_heredocs(t_frame *frame);
int 		set_hd_as_infd(t_frame *frame);
void		clean_tmp(t_frame *frame);
void		remove_hd(t_frame *frame);
int			sig_flag_hd(int action);
void		add_hd_name_to_list(t_frame *frame);
void		interrupt_rmv_hd(t_frame *frame);
void		close_all_fd(t_frame *frame);

void		reset_frame(t_frame *frame);
#endif