#include "minishell.h"

int	main(void)
{
	char		*str;
	t_frame		frame;

	init_frame(&frame);
	get_env(&frame);
	//save_builtins(&frame);
	while (1)
	{
		str = init_signals_and_prompt(&frame);
		// frame.shell_env_start->con = "A B ";
		// frame.shell_env_start->name= "a";
		//str = "export tmp_test=\"/bin/echo 1\" $tmp_test";
		//str = "echo $OS_ACTIVITY_DT_MODE '2'";
		//str = "echo \"1\"A B \"'2'";
		//str = "echo >file1";
		if (str == NULL)
		{
			exit_minishell(&frame);
			free_all(&frame);
			exit(frame.e_status);
		}
		if (str[0] != '\0')
		{
			ft_minishell(str, &frame);
			add_history(str);
			free(str);//SIGABRT
			reset_frame(&frame);
			// break ;
		}
	}
}

//TODO norm

//TODO funktionen: malloc + protection, print_error, free_all, exit+status




// ./minishell fuehrt export aus

/* unset PATH
ls
cd /bin/../bin/
ls
 */
