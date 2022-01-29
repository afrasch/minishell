#include "../includes/minishell.h"

void add_to_hd_list(t_frame *frame, char *path)
{
	if (frame->hd_list == NULL)
		ft_lstnew((void *) path);
	else
		ft_lstadd_back(&frame->hd_list, ft_lstnew((void *) path));
}

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
		if (access(buf, F_OK) != 0)
			break ;
	}
	close(fd);
	return (ft_strdup(buf));
}

void	remove_hd(t_frame *frame)
{
	if (unlink(frame->cc->hd_path) != 0)
	{
		frame->cc->cc_errno = errno;
		printf("Error");
	}
}
