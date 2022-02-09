#include "../includes/minishell.h"

int	check_slashes(t_node *node, t_frame* frame)
{
	if (ft_strncmp(node->content, "/", 1) == 0)
	{
		if (access(node->content, F_OK) < 0)
		{
			frame->e_status = 127;
			return (print_error(errno, node->content, NULL, NULL));//nsfod
		}
		else
			return (print_error(-2, node->content, NULL, "is a directory"));
	}
	return (0);
}

int	check_redir(t_node *node)
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

int	check_end_quotes(t_node *node)
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

int	check_pipes(t_frame	*frame)
{
	t_chunk	*cc;

	cc = frame->cc;
	if ((cc->prev != NULL && cc->prev->node_start == NULL && cc->prev->expanded == OFF)
		|| (cc->next != NULL && cc->next->node_start == NULL && cc->next->expanded == OFF))
	{
		frame->e_status = 258;
		return (print_error(-2, "|", NULL, "syntax error near unexpected token"));
	}
	return (0);
}

int control_chunk(t_frame* frame)
{
	if (check_pipes(frame) == ERROR)
		return (ERROR);
	return (0);
}

int control_nodes_raw(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		if (control_chunk(frame) < 0)
			return (ERROR);
		// TODO syntax error // TODO return val
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL)
		{
			if (control_node(frame->cc->cn, frame) < 0)
				return (ERROR);//TODO error syntax error frame mit schicken zum freen, da wo Fehler auftritt Error aufrufen
			frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
	return (0);
}
