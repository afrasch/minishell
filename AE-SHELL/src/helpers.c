#include "../includes/minishell.h"

void	set_list_2start(t_frame *frame)
{
	frame->cc = frame->chunk_start;
	/* while (frame->cn->prev != NULL)
		frame->cn = frame->cn->prev; */
}

int	is_alnum_uscore(char c)
{
	if (ft_isalnum(c) != 0 || c == '_')
		return (1);
	return(0);
}

void ft_print_stack(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		printf("New Chunk\n");
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL)
		{
			printf("%s\n", frame->cc->cn->content);
			frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
}

void	print_var(t_frame *frame)
{
	frame->shell_env = frame->shell_env_start;
	while (frame->shell_env != NULL)
	{
		printf("name: %s, content: %s \n", frame->shell_env->name, frame->shell_env->con);
		frame->shell_env = frame->shell_env->next;
	}
}