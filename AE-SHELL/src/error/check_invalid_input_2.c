#include "minishell.h"

static int	check_slashes(t_node *node, t_frame* frame)
{
	if (ft_strncmp(node->content, "/", 1) == 0)
	{
		if (access(node->content, F_OK) < 0)
		{
			frame->e_status = 127;
			return (print_error(errno, node->content, NULL, NULL));//nsfod
		}
		else if (!node->next->content)
			return (print_error(-2, node->content, NULL, "is a directory"));
	}
	return (0);
}

static int	check_redir(t_node *node)
{
	if (node->type == S_REDIR_L || node->type == S_REDIR_R || node->type == D_REDIR_L
		|| node->type == D_REDIR_R)
	{
		if (node->next)
		{
			if ((node->type == D_REDIR_R && node->next->type != WORD)
				|| (node->type == D_REDIR_L && node->next->type == D_REDIR_L)
				|| (node->type == D_REDIR_L && node->next->type == S_REDIR_R))
				return (print_error(errno, node->next->content, NULL, "syntax error near unexpected token"));
			if (node->type != D_REDIR_L && node->next->type == WORD
				&& access(node->next->content, F_OK) == ERROR && node->type != S_REDIR_R)
				return (print_error(errno, node->next->content, NULL, "No such file or directory"));
		}
		else
			return (print_error(errno, "newline", NULL, "syntax error near unexpected token"));
	}
	return (0);
}

static int	check_end_quotes(t_node *node)
{
	if (node->quote_st == SINGLE_Q)
		return (print_error(-2, "\'", NULL, "syntax error near single quotes"));
	if (node->quote_st == DOUBLE_Q)
		return (print_error(-2, "\"", NULL, "syntax error near double quotes"));
	return (0);
}

int	control_node(t_node *node, t_frame *frame)
{
	if (check_redir(node) == ERROR
		|| check_end_quotes(node) == ERROR
		|| check_slashes(node, frame) == ERROR)
		return (ERROR);
	return (0);
}
