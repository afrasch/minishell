#include "minishell.h"

int	cd(t_frame *frame)
{
	t_node	*node;
	char	*home_path;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	node = frame->cc->node_start;
	home_path = get_env_var(frame, "HOME");
	if (!oldpwd || !node || !home_path)
		return (2);
	if (node->next == NULL)
	{
		if (chdir(home_path)== ERROR)
		{
			// print_error(SHELLNAME, node->content, NULL, "Home path not set");
			print_error(errno, node->content, NULL, "Home path not set");
			return (2);
		}
	}
	else
	{
		if (chdir(node->next->content) == ERROR)
		{
			// print_error_errno(SHELLNAME, node->content, node->next->content);
			// print_error(SHELLNAME, node->content, node->next->content, "No such file or directory");
			print_error(errno, node->content, node->next->content, NULL);
			return (2);//exit?
		}
	}
	update_env(frame, "PWD", node->content, oldpwd);
	return (0);
}
