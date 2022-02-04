#include "../includes/minishell.h"

static char	*expand_hd(char *str, int *i)
{
	char	*var_name;

	var_name = ft_calloc(1, sizeof(char));
	while (str[*i + 1] && (is_alnum_uscore(str[*i + 1])) == 1)
	{
		var_name = ft_add_chr_to_str(var_name, str[*i + 1]);
		(*i)++;
	}
	return (var_name);
}

static void	handle_hd_expansion(t_frame *frame, char *str)
{
	int i = 0;
	char	*var_name = NULL;

	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = expand_hd(str, &i);
			var_name = get_env_var(frame, var_name);
			ft_putstr_fd (var_name, frame->cc->in_fd);
			if (!var_name)
				free(var_name);
			var_name = NULL;//TODO eigene funktion ft_free
		}
		else
			ft_putchar_fd(str[i], frame->cc->in_fd);
		i++;
	}
	ft_putchar_fd('\n', frame->cc->in_fd);
}

int	do_here_doc(t_frame *frame)//TODO kontrolliere sig flag
{
	char	*str;
	char	*del;

	del = frame->cc->cn->next->content;
	while (1)
	{
		str = get_heredoc_prompt();
		if (!str)
			break ;
		if (ft_strncmp(str, del, ft_strlen(del)) == 0)
		{
			free (str);
			break ;
		}
		if (frame->cc->cn->next->word == NO_Q)
			handle_hd_expansion(frame, str);
		else
			ft_putendl_fd(str, frame->cc->in_fd);
		free(str);
	}
	if (sig_flag_hd(SHOW) == ON)
	{
		close(frame->cc->in_fd);
		return (-1);
	}
	return (0);
}

int	set_fd_here_doc(t_frame *frame)//TODO path fuer TMP datei
{
	char	*name;

	name = NULL;
	if (frame->cc->hd_bool == OFF)
	{
		name = create_rand_name();
		// frame->cc->hd_path = ft_strjoin("../minishell/tmp",name);
		frame->cc->hd_path = ft_strjoin("/Users/afrasch/wokspace/minishell/esra/AE-SHELL/tmp",name);
		frame->cc->hd_bool = ON;
		add_hd_name_to_list(frame);
		free(name);
		name = NULL;
	}
	else
		remove_hd(frame);
	frame->cc->in_fd  = open(frame->cc->hd_path, O_RDWR | O_CREAT | O_TRUNC, 0777);//TODO open_protected
	if (frame->cc->in_fd < 0)
	{
		frame->cc->cc_errno = errno;
		perror(strerror(frame->cc->cc_errno));//TODO error, exit
		return (ERROR);
	}
	if (do_here_doc(frame) < 0)
		return (-1);
	close(frame->cc->in_fd);//TODO protect every open() and close()
	frame->cc->in_fd = open(frame->cc->hd_path, O_RDONLY, 0777);
	if (frame->cc->in_fd < 0)
	{
		frame->cc->cc_errno = errno;
		perror(strerror(frame->cc->cc_errno));
		return (ERROR);
	}
	return (0);
}

int	set_here_docs(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->in_fd > 3)
		close(frame->cc->in_fd);
	if (set_fd_here_doc(frame)< 0)
		return (-1);
	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (0);
}

int	solve_heredocs(t_frame *frame)//TODO error management gemeinsam
{
	int		std_in;

	frame->cc = frame->chunk_start;
	std_in = dup(STDIN_FILENO);
	while (frame->cc != NULL)
	{
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL)
		{
			if (frame->cc->cn->type == D_REDIR_L)
			{
				if (set_here_docs(frame) < 0)
				{
					dup2(std_in, STDIN_FILENO);
					close(std_in);
					return (ERROR);
				}
			}
			else
				frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
	frame->cc = frame->chunk_start;
	dup2(std_in, STDIN_FILENO);
	close(std_in);
	return (0);
}
