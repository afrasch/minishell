#include "../includes/minishell.h"

/* Save the environment variables in a list, name and content separately. */
void	set_environment_list(t_env *env)
{
	extern char	**environ;// oder mit getenv("var_name")?
	int			i;
	int			j;

	i = 0;
	//create list (ft_lstnew ?)
	while (environ[i] + 1)
	{
		j = 0;
		while (environ[i][j] != '=')
		{
			ft_add_chr_to_str(env->name, environ[i][j]);
			j++;
		}
		j++;//jump over '=' -> muss beim env printen zwischen name und var_content eingefügt werden
		while (environ[i][j])
		{
			ft_add_chr_to_str(env->con, environ[i][j]);
			j++;
		}
		i++;
		//add node to list
		env = env->next;
	}
}

// "export" auch handeln? -> zählt zusätzlich zu env auch variables ohne '=' auf
void	print_env(t_env *env)// aufgerufen if (ft_strncmp(str, "env", 3) == 0)
{
	while (env != NULL && env->con != NULL)
	{
		if (env->con != NULL)
			printf("%s=%s\n", env->name, env->con);
		else
			printf("%s=\n", env->name);
		env = env->next;
	}
}

void	export(char *variable, t_env *env)// aufgerufen nach "export " mit variablen string (eg. a=4)
{
	int	i;

	i = 0;
	//create new env list element
	if (ft_strchr(variable, '=') != NULL)// variables werden nur im env abgespeichert, wenn '=' dabei
	{
		while (variable[i] != '=' && variable[i])//je nachdem ob wir variable null terminiert eingeben
		{
			ft_add_chr_to_str(env->name, variable[i]);
			i++;
		}
		i++;
		while (variable[i])
		{
			ft_add_chr_to_str(env->con, variable[i]);
			i++;
		}
	}
}

void	unset(char *variable, t_env *env);//search for variable in env list and delete whole node
