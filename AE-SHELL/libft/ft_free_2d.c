#include "libft.h"

void	ft_free_2d(void ***to_free)
{
	int	i;

	if (*to_free == NULL || to_free == NULL)
		return ;
	i = 0;
	while ((*to_free)[i])
	{
		free((*to_free)[i]);
		(*to_free)[i] = NULL;
		i++;
	}
	free(*to_free);
	*to_free = NULL;
}