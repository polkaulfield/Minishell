#include "../../includes/minishell.h"

/*char	**path_execute(char *cmd, t_sh *sh)
{
	char	**cmd;


}*/

void	in_file(t_sh)


void	excute(t_sh *sh)
{
	//cmd = path_execute(sh->cmd_list->cmd, sh);
	sh->cmd_list->pid = fork();
	if (sh->cmd_list->pid == -1)
	{
		printf("Fork Error\n");
		terminate(sh);
	}
	else if (sh->cmd_list->pid == 0)
	{
		execve(sh->cmd_list->cmd[0], sh->cmd_list->cmd, sh->env);
		printf("Commando not Found\n");
		exit(1);
	}
	int status;
	sh->cmd_list->pid = wait(&status);
	//printf("todo bien\n");
}


/*void	free_memory(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i] || arr[i + 1])
		if (arr[i])
			free(arr[i]);
	free(arr);
}

void	emergency_exit(char *func_error, char **arr)
{
	if (arr)
		free_memory(arr);
	perror(func_error);
	exit(1);
}

int	path_explorer(char **env, char ***arr, char **path, char *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i] && ft_strncmp(env[i], "PATH=", 4) != 0)
		;
	if (!env[i])
		return (1);
	env[i] = ft_strchr(env[i], '=');
	*arr = ft_split(++env[i], ':');
	i = -1;
	while ((*arr)[++i])
	{
		tmp = ft_strjoin((*arr)[i], "/");
		*path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!(*path))
			return (1);
		if (access(*path, F_OK) == 0)
			break ;
		free(*path);
		*path = NULL;
	}
	return (0);
}

char	*ft_path_finder(char **env, char *cmd)
{
	char	*path;
	char	**arr;

	if (path_explorer(env, &arr, &path, cmd))
	{
		if (arr)
			free_memory(arr);
		free(cmd);
		return (NULL);
	}
	free_memory(arr);
	if (!path)
	{
		return (cmd);
	}
	free(cmd);
	return (path);
}

char	**parser_cmd(char *cmd, char **env)
{
	char	**argv;

	argv = ft_split(cmd, ' ');
	if (!argv)
		return (NULL);
	argv[0] = ft_path_finder(env, argv[0]);
	if (!argv[0])
	{
		free_memory(argv);
		return (NULL);
	}
	return (argv);
}*/
