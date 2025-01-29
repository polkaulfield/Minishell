#include "../../includes/minishell.h"

void	join_line_val(char **line, char **val)
{
	ft_strlcat(*line, *val, ft_strlen(*line) + ft_strlen(*val) + 1);
}

char	*linejoin(char *user, char *path, t_sh *sh)
{
	char	*div1;
	char	*div2;
	char	*line;

	if (!user)
		user = "?";
	if (!path)
		path = "?";
	div1 = ":";
	div2 = "$\n> ";
	line = galloc((ft_strlen(user) + ft_strlen(div1) + \
		ft_strlen(path) + ft_strlen(div2) + 1), sh);
	line[0] = '\0';
	join_line_val(&line, &user);
	join_line_val(&line, &div1);
	join_line_val(&line, &path);
	join_line_val(&line, &div2);
	return (line);
}

char	*userjoin(char *user, char *pc, t_sh *sh)
{
	char	*div1;
	char	*line;

	if (!user)
		user = "?";
	if (!pc)
		pc = "?";
	div1 = "@";
	line = galloc((ft_strlen(user) + ft_strlen(div1) + ft_strlen(pc) + 1), sh);
	line[0] = '\0';
	join_line_val(&line, &user);
	join_line_val(&line, &div1);
	join_line_val(&line, &pc);
	return (line);
}

// strlen till the char
int	ft_lentoc(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
