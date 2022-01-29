#include "../includes/minishell.h"

void	clean_tmp(t_frame *frame)
{
	t_list	*tmp;

	while(frame->hd_list != NULL)
	{
		tmp = frame->hd_list;
		remove(frame->hd_list->content);
		free(tmp->content);
		frame->hd_list = frame->hd_list->next;
		free(tmp);
		tmp = NULL;
	}
}

/* void	reset_frame(frame)
{

} */