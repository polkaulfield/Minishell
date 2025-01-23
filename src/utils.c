#include "../includes/minishell.h"

// strlen till the char
int	ft_lentoc(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
