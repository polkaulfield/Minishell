#include "../includes/minishell.h"

char	*linejoin(char *user, char *path, t_sh *sh)
{
	char	*div1;
	char	*div2;
	char	*line;
	int		i;
	int		j;

	if (!user)
		user = "?";
	if (!path)
		path = "?";
	div1 = ":";
	div2 = "$\n>";
	line = galloc((ft_strlen(user) + ft_strlen(div1) + ft_strlen(path) + ft_strlen(div2) + 1) * sizeof(char), sh);
	i = -1;
	j = -1;
	while (user[++i])
		line[++j] = user[i];
	i = -1;
	while (div1[++i])
		line[++j] = div1[i];
	i = -1;
	while (path[++i])
		line[++j] = path[i];
	i = -1;
	while (div2[++i])
		line[++j] = div2[i];
	line[++j] = '\0';
	return (line);
}

char	*userjoin(char *user, char *pc, t_sh *sh)
{
	char	*div1;
	char	*line;
	int		i;
	int		j;

	if (!user)
		user = "?";
	if (!pc)
		pc = "?";
	div1 = "@";
	line = galloc((ft_strlen(user) + ft_strlen(div1) + ft_strlen(pc) + 1) * sizeof(char), sh);
	i = -1;
	j = -1;
	while (user[++i])
		line[++j] = user[i];
	i = -1;
	while (div1[++i])
		line[++j] = div1[i];
	i = -1;
	while (pc[++i])
		line[++j] = pc[i];
	line[++j] = '\0';
	return (line);
}

//ahora el nombre esta recortado de cXrXXsX.42barcelona.com a cXrXsX
//si se ejecuta en otro pc que no sea de 42 el nombre deberia salir entero
char	*user_finder(char *user, char *pc, t_sh *sh)
{
	char	*line_user;

	user = ft_substr(getenv("USER"), 0, ft_strlen(getenv("USER")));
	add_galloc(user, sh);
	pc = ft_strchr(getenv("SESSION_MANAGER"), '/');
	pc++;
	pc = ft_substr(pc, 0, ft_lentoc(pc, '.'));
	add_galloc(pc, sh);
	if (!user)
		user = "?";
	if (!pc)
		pc = "?";
	line_user = userjoin(user, pc, sh);
	if (!line_user)
		return ("?");
	return (line_user);
}

char	*path_finder(char *path, t_sh *sh)
{
	char	*line_path;
	int		home_size;

	path = getenv("PWD");
	if (!path)
		return ("?");
	line_path = galloc((strlen(path) + 1) * sizeof(char), sh);
	if (!line_path)
		return ("?");
	line_path = ft_substr(path, 0, ft_strlen(path));
	add_galloc(line_path, sh);
	if (ft_strncmp(getenv("HOME"), line_path, ft_strlen(getenv("HOME"))) == 0)
	{
		home_size = ft_strlen(getenv("HOME"));
		line_path = ft_substr(path, home_size - 1, ft_strlen(path) - home_size + 1);
		line_path[0] = '~';
		add_galloc(line_path, sh);
	}
	return (line_path);
}

char	*line_finder(t_sh *sh)
{
	char	*line_user;
	char	*line_path;
	char	*line;

	line_user = user_finder(getenv("LOGNAME"), getenv("SESSION_MANAGER"), sh);
	line_path = path_finder("PWD", sh);

	line = linejoin(line_user, line_path, sh);
	if (!line)
		return ("?$\n>");

	return (line);
}
