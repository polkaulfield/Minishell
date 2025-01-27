#include "../../includes/minishell.h"



void	in_file(t_sh *sh)
{
	if (sh->cmd_list->fd_in_red)
		sh->cmd_list->fd_in = open(sh->cmd_list->infile, O_RDONLY);
	else
		sh->cmd_list->fd_in = open(sh->cmd_list->infile, O_RDONLY);
	if (sh->cmd_list->fd_in < 0)
	{
		printf("infile error\n");
		exit(1);
	}
	dup2(sh->cmd_list->fd_in, STDIN_FILENO);
	close(sh->cmd_list->fd_in);
}

void	out_file(t_sh *sh)
{
	if (sh->cmd_list->fd_out_red)
		sh->cmd_list->fd_out = open(sh->cmd_list->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		sh->cmd_list->fd_out = open(sh->cmd_list->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (sh->cmd_list->fd_out < 0)
	{
		printf("outfile error\n");
		exit(1);
	}
	dup2(sh->cmd_list->fd_out, STDOUT_FILENO);
	close(sh->cmd_list->fd_out);
}

t_cmd	*fork_create(t_sh *sh)
{
	t_cmd	*cmd;

	sh->cmd_list = sh->cmd_list->start;
	cmd = sh->cmd_list;
	while (cmd)
	{
		cmd->pid = fork();
		if (cmd->pid)
			cmd = cmd->next;
		else
			return (cmd);
	}
	return (sh->cmd_list);
}

void	prepare_pipe(t_sh *sh)
{
		t_cmd *cmd;
	if (sh->cmd_list->in_pipe)
		dup2(sh->cmd_list->fd_pipe[0], STDIN_FILENO);
	if (sh->cmd_list->out_pipe)
		dup2(sh->cmd_list->next->fd_pipe[1], STDOUT_FILENO);
	cmd = sh->cmd_list->start;
	while (cmd)
	{
		if (cmd->fd_pipe)
		{
			close(cmd->fd_pipe[0]);
			close(cmd->fd_pipe[1]);
		}
		cmd = cmd->next;
	}
}

//cmd = path_execute(sh->cmd_list->cmd, sh);
	//sh->cmd_list->pid = fork();
void	excute(t_sh *sh)
{
	t_cmd	*temp_cmd;

	//printf("process\n");
	if (sh->cmd_list->pid == -1)
	{
		printf("Fork Error\n");
		terminate(sh);
	}
	else if (sh->cmd_list->pid == 0)
	{
		if (sh->cmd_list->infile)
			in_file(sh);
		if (sh->cmd_list->outfile)
			out_file(sh);
		prepare_pipe(sh);
		execve(sh->cmd_list->cmd[0], sh->cmd_list->cmd, sh->env);
		printf("minishell: Command not Found\n");
		exit(1);
	}
	sh->cmd_list = sh->cmd_list->start;
	temp_cmd = sh->cmd_list;
	while (temp_cmd)
	{
		if (temp_cmd->fd_pipe)
		{
			close(temp_cmd->fd_pipe[0]);
			close(temp_cmd->fd_pipe[1]);
		}
		temp_cmd = temp_cmd->next;
	}
	temp_cmd = sh->cmd_list->start;
	while (temp_cmd)
	{
		waitpid(temp_cmd->pid, NULL, 0);
		temp_cmd = temp_cmd->next;
	}
}

/*char	**path_execute(char *cmd, t_sh *sh)
{
	char	**cmd;


}*/

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
