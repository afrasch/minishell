#include "../includes/minishell.h"

/* void	clean_tmp(t_frame *frame)
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
} */

/* 
THINGS TO FREE:
at the end:
- Shell_env
- 

after loop:
- str von readline
- alle chunks

 */

void	reset_frame(char *str, t_frame *frame)
{
	free(str);
	

}