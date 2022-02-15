#include "minishell.h"

int	pwd(t_frame *frame)
{
	char	*current_path;

	current_path = ft_strdup(getcwd(NULL, 0));
	if (current_path == NULL)
		return (2);
	write(frame->cc->out_fd, current_path, ft_strlen(current_path));
	write (frame->cc->out_fd, "\n", 1);
	return (0);
}
