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
		//str = "export a";
		//str = "\" echo \"  \" cat";
		//str = "export a b c d";
		// str = "<file1 | wc";
		if (str == NULL)
		{
			exit_minishell(&frame);
			break ;
		}
		if (str[0] != '\0')
		{
			ft_minishell(str, &frame);
			add_history(str);
			free(str);//SIGABRT
			reset_frame(&frame);
		}
	}
}
//TODO norm

//TODO funktionen: malloc + protection, print_error, free_all, exit+status