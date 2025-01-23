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

char	*user_finder(char *user, char *pc, t_galloc *l_galloc)
{
	char	*line_user;

	user = "?";
	pc = "?";
	if (l_galloc)
		;
	user = ft_substr(getenv("USERNAME"), 0, ft_strlen(getenv("USERNAME")));
	pc = ft_strchr(getenv("SESSION_MANAGER"), '/');
	pc++;
	pc = ft_substr(pc, 0, ft_lentoc(pc, ':'));
	if (!user)
		user = "?";
	if (!pc)
		pc = "?";
	line_user = ft_strjoin(user, ft_strjoin("@", pc));
	if (!line_user)
		return ("?");
	return (line_user);
}

char	*path_finder(char *path, t_galloc *l_galloc)
{
	char	*line_path;

	path = NULL;
	path = getenv("PWD");
	if (!path)
		return ("?");
	line_path = galloc((strlen(path) + 1) * sizeof(char), l_galloc);
	if (!line_path)
		return ("?");
	line_path = ft_substr(path, 0, ft_strlen(path) + 1);
	return (line_path);
}

char	*line_finder(t_galloc *l_galloc)
{
	char	*line_user;
	char	*line_path;
	char	*line;

	line_user = user_finder(getenv("LOGNAME"), getenv("SESSION_MANAGER"), l_galloc);
	line_path = path_finder("PWD", l_galloc);
	line = ft_strjoin(line_user, ft_strjoin(":", ft_strjoin(line_path, "$\n>")));
	if (!line)
		return ("?$\n>");
	return (line);
}

int	main(void)
{
	char	*input;
	char	*line;
	t_galloc	*l_galloc;

	l_galloc = NULL;
	while(1)
	{
		line = line_finder(l_galloc);
		if (!line)
			line = "?";
		input = readline(line);
		if (!input)
			return (1);
		printf("%s\n", input);
		free(input);
	}
	return (0);
}
