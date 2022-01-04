#include "libft.h"

void	ft_free_1d(void **to_free)
{
	if (*to_free == NULL)
		return ;
	free(*to_free);
	*to_free = NULL;
}