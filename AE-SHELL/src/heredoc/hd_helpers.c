#include "../includes/minishell.h"

char *create_rand_name()
{
	int fd = open("/dev/random", O_RDONLY);
	char buf[10];
	int	i;

	while(1)
	{
		i = 0;
		read(fd, buf, 9);
		buf[9] = '\0';
		while (buf[i])
		{
			buf[i] = (buf[i] * buf[i]) % 25 + 'a';
			i++;
		}
		if (access(buf, F_OK) != 0)//TODO free buf?
			break ;
	}
	close(fd);
	return (ft_strdup(buf));
}

void	remove_hd(t_frame *frame)//TODO remove after cd
{
	if (unlink(frame->cc->hd_path) != 0)
	{
		frame->cc->cc_errno = errno;
		printf("Error");//TODO error
	}
}

void	interupt_rmv_hd(t_frame *frame)
{
	t_hd_list *node;
	t_hd_list *tmp;

	node = frame->hd_list;
	while (node!= NULL)
	{
		tmp = node;
		unlink(node->name_of_hd);//TODO protection
		free(node->name_of_hd);
		node->name_of_hd = NULL;
		free(node);
		node = NULL;
		node = tmp->next;
	}
	frame->hd_list = NULL;
	close_all_fd(frame);
}

void	add_hd_name_to_list(t_frame *frame)
{
	t_hd_list	*new_node;
	t_hd_list 	*tmp;


	tmp = frame->hd_list;
	new_node = ft_calloc(1, sizeof(t_hd_list));
	if (tmp == NULL)
	{
		frame->hd_list = new_node;
		frame->hd_list->name_of_hd = ft_strdup(frame->cc->hd_path);
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		new_node->next = NULL;
		tmp->next  = new_node;
		tmp->next->name_of_hd = ft_strdup(frame->cc->hd_path);
	}
}
