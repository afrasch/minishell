/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:41:55 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 21:23:31 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define SHELLNAME	"SHELL SHOCK: "
# define ON 1
# define OFF 0
# define SHOW 3
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define PIPEIN -4
# define PIPEOUT -5
# define NO_PIPE -6
# define E_STATUS 1
# define STAT_LOC 0

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
}	t_builtin;

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
	D_REDIR_L,
	D_REDIR_R,
	WORD,
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
}	t_node;

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
	char				**cmd_arr;
	int					hd_bool;
	char				*hd_path;
	int					expanded;
	int					e_status_file;
}	t_chunk;

typedef struct s_frame
{
	t_var				*shell_env;
	t_var				*shell_env_start;
	char				**env_copy;
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
	int					pid;
}	t_frame;

typedef struct s_exec
{
	int	fd[2];
	int	tmp_fd;
}	t_exec;

void		split_in_chunks(char *str, t_frame *frame);
void		add_letter(char c, t_frame *frame);
void		handle_quotes(t_frame *frame);
void		set_quote_state(char c, t_frame *frame);
void		set_quote_state_2(char c, t_frame *frame);
void		tag_node(t_node *node);
int			set_right_red(t_frame *frame);
int			set_left_red(t_frame *frame);
void		check_exp_var(char *var_name, t_frame *frame);
void		q_var_expansion(char *str, t_frame *frame);
void		uq_var_expansion(char *str, t_frame *frame);
int			check_spaces(char c);
void		expand(char *str, int *i, t_frame *frame);
int			expand_requisites(t_frame *frame, char cur_c, char next_c);
int			execute_chunks(t_frame *frame);
int			check_for_redir(t_frame *frame);
void		get_path(t_frame *frame);
int			execute_builtin(t_frame *frame, char *cmd);

void		init_frame(t_frame *frame);
void		next_node(t_frame *frame);
void		next_chunk(t_frame *frame);
void		free_node(t_node *node);
void		init_chunk(t_frame *frame);
void		init_node(t_frame *frame);
int			lstsize(t_node *lst);
int			var_lstsize(t_var *lst);
void		set_list_2start(t_frame *frame);
int			add_var_node(t_frame *frame, char *name,
				char *content, int just_export);
int			is_alnum_uscore(char c);
int			is_valid_varname(char *name);

int			input_check(t_frame *frame);
int			control_node(t_node *node, t_frame *frame);
void		delete_node(t_frame	*frame, t_node *node);
void		delete_var_node(t_frame	*frame, t_var *node);
char		**list_to_arr(t_node *node_start, t_frame *frame);
char		**env_list_to_arr(t_frame *frame);
void		re_arrange_list(t_frame *frame);
t_builtin	check_for_builtin(char *input_cmd, t_frame *frame);
char		*ft_quote(char *str, t_frame *frame);
char		*ft_unquote(char *str);

void		get_env(t_frame *frame, char **env);
char		*get_env_var(t_frame *frame, char *name);
void		replace_env_var(t_frame *frame, char *name, char *new_content);
int			look_for_var(t_frame *frame, char *name);
void		update_env(t_frame *frame, char *name, char *content, char *oldpwd);

void		ft_print_stack(t_frame *frame);
void		ft_print_stack_plain(t_frame *frame);
void		debug_print(t_frame *frame);
void		debug_print_full(t_frame *frame);
void		print_hd_list(t_frame *frame);

char		*change_caps(char *input_cmd);
int			print_error(char *cmd, char *arg, char *message);
void		print_signal_error(int sig);
char		*init_signals_and_prompt(t_frame *frame);
void		child_killer(int signal);
void		clear_signals(void);
void		child_killer_one_cmd(int sig);

int			ft_fork(t_frame *frame);
void		init_exec(t_exec *exec);
void		check_for_pipe(t_frame *frame);
void		wait_for_childs(t_frame *frame);
int			ft_childprocess(t_frame *frame, t_exec *exec, char *cmd);
void		ft_parent(t_frame *frame, t_exec *exec, t_chunk *cc);
int			get_access(t_frame *frame, char	*cmd);
int			execute_one_cmd(t_frame *frame, t_exec *exec);
int			execute_cmd(t_frame *frame, int i, char *cmd);
void		prepare_builtin_alone(t_frame *frame);
void		set_back_builtin_alone(t_frame *frame);

void		exit_minishell(t_frame *frame);
int			env(t_frame *frame);
int			unset(t_frame *frame);
int			export(t_frame *frame);
int			pwd(t_frame *frame);
int			cd(t_frame *frame);
int			echo(t_frame *frame);

char		*create_rand_name(void);
int			set_here_docs(t_frame *frame);
int			do_here_doc(t_frame *frame);
char		*get_heredoc_prompt(void);
void		handle_hd_expansion(t_frame *frame, char *str);
int			solve_heredocs(t_frame *frame);
int			set_hd_as_infd(t_frame *frame);
void		remove_hd(t_frame *frame);
int			sig_flag_hd(int action);
void		add_hd_name_to_list(t_frame *frame);
void		interrupt_rmv_hd(t_frame *frame);

void		reset_frame(t_frame *frame);
void		free_env(t_frame *frame);
void		free_all(t_frame *frame);
int			error_exit(t_frame *frame);
void		exec_scmd_free_exit(int status, char **argv, t_list *l_free);
int			print_error_errno(char *s1, char *s2, char *s3);
void		print_error_exit(t_frame *frame, char *cmd, char *message);

char		*minishell_get_next_line(int fd);
void		*ft_calloc_mini(size_t count, size_t size, t_frame *frame);
#endif