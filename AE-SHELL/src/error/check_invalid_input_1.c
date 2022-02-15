#include "minishell.h"

static int	check_pipes(t_frame	*frame)
{
	t_chunk	*cc;

	cc = frame->cc;
	if ((cc->prev != NULL && cc->prev->node_start == NULL && cc->prev->expanded == OFF)
		|| (cc->next != NULL && cc->next->node_start == NULL && cc->next->expanded == OFF))
	{
		frame->e_status = 258;
		return (print_error(SHELLNAME, "`|'", NULL, "syntax error near unexpected token"));
		// return (print_error(-2, "|", NULL, "syntax error near unexpected token"));
	}
	return (0);
}

static int control_chunk(t_frame* frame)
{
	if (check_pipes(frame) == ERROR)
		return (ERROR);
	return (0);
}

int input_check(t_frame *frame)
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
				return (ERROR);//TODO syntax error frame mit schicken zum freen, da wo Fehler auftritt Error aufrufen
			frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
	return (0);
}
