#include "minishell.h"

int	cd(t_frame *frame)
{
	t_node	*node;
	char	*home_path;
	char	*oldpwd;

	//oldpwd = getcwd(NULL, 0); TODO loeschen
	node = frame->cc->node_start;
	home_path = get_env_var(frame, "HOME");
	oldpwd = get_env_var(frame, "OLDPWD"); //freen
	if (!oldpwd || !node || !home_path)
	{
		if (!oldpwd)
			print_error("cd", NULL, "OLDPWD not set");
		if (!home_path)
			print_error("cd", NULL, "HOME not set");
		return (2);
	}
	if (node->next == NULL)
	{
		if (chdir(home_path)== ERROR)
		{
			print_error(node->content, NULL, "Home path not available");
			return (2);
		}
	}
	else
	{
		if (chdir(node->next->content) == ERROR)
		{
			print_error(node->content, node->next->content, NULL);
			return (2);
		}
	}
	update_env(frame, "PWD", node->content, oldpwd);
	return (0);
}
