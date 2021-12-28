#include "../includes/minishell.h"

int	main(void)
{
	char		*str;
	t_frame		frame;

	init_frame(&frame);
	while (1)
	{
		//str = readline(PROMPT);
		str = "\"hi>\">";
		ft_lexer(str, &frame);
		if (ft_strlen(str) > 0)
			add_history(str);
	}
}
