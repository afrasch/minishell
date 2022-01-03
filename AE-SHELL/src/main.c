#include "../includes/minishell.h"

int	main(void)
{
	char		*str;
	t_frame		frame;

	init_frame(&frame);
	while (1)
	{
		str = readline(PROMPT);
		//str = NULL;
		//str[0] = '\0';
		if (str[0] != '\0')
		{
			ft_lexer(str, &frame);
			add_history(str);
			ft_print_stack(&frame);
		}
		reset_frame(&frame);
		free(str);
		str = NULL;
		//break ;
	}
}
