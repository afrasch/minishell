#include "../includes/minishell.h"

int	main(void)
{
	char		*str;
	t_frame		frame;

	init_frame(&frame);
	while (1)
	{
		str = readline(PROMPT);//ctrl+D -> EOF
		//str = "\"e \" | i | $ ";
		if (ft_strncmp(str, "exit", 4) == 0)
		{
			free(str);
			exit(EXIT_SUCCESS);
		}
		if (str[0] != '\0')
		{
			ft_lexer(str, &frame);
			add_history(str);
			//ft_print_stack(&frame);
		}
		//reset_frame(&frame);
		/* if (str != NULL)
		{
			//free(str);
			//str = NULL;
		} */
		//break ;
	}
}
