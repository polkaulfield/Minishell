#include "../../includes/minishell.h"

//void	echo_built_int()

void	find_built_in(char *input, t_sh *sh)
{
	if (ft_strncmp(input, "echo", ft_strlen(input)) == 0)
		;
	else if (ft_strncmp(input, "cd", ft_strlen(input)) == 0)
		sh->cmd_list->main_proces = 1;
	else if (ft_strncmp(input, "pwd", ft_strlen(input)) == 0)
		;
	else if (ft_strncmp(input, "export", ft_strlen(input)) == 0)
		;
	else if (ft_strncmp(input, "unset", ft_strlen(input)) == 0)
		;
	else if (ft_strncmp(input, "env", ft_strlen(input)) == 0)
		;
	else if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
<<<<<<< Updated upstream
		sh->cmd_list->main_proces = 1;
	else
		return ;
	sh->cmd_list->built_in = 1;
=======
	{
		sh->cmd_list->main_proces = 1;
		sh->cmd_list->built_in = 1;
	}
	/*else
		sh->cmd_list->built_in = 0;*/
>>>>>>> Stashed changes
}

int	exec_built_in(t_sh *sh)
{
	if (ft_strncmp(sh->cmd_list->cmd[0], "echo", ft_strlen(sh->cmd_list->cmd[0])) == 0)
		echo(sh);
	else if (ft_strncmp(sh->cmd_list->cmd[0], "cd", ft_strlen(sh->cmd_list->cmd[0])) == 0)
	{
		//printf("We are in CD count = %d\n", sh->cmd_list->cmd_count);
		if (sh->cmd_list->cmd_count > 0)
			cd(sh);
	}
	else if (ft_strncmp(sh->cmd_list->cmd[0], "pwd", ft_strlen(sh->cmd_list->cmd[0])) == 0)
		printf("pwd\n");
	else if (ft_strncmp(sh->cmd_list->cmd[0], "export", ft_strlen(sh->cmd_list->cmd[0])) == 0)
		printf("export\n");
	else if (ft_strncmp(sh->cmd_list->cmd[0], "unset", ft_strlen(sh->cmd_list->cmd[0])) == 0)
		printf("unset\n");
	else if (ft_strncmp(sh->cmd_list->cmd[0], "env", ft_strlen(sh->cmd_list->cmd[0])) == 0)
		printf("env\n");
	else if (ft_strncmp(sh->cmd_list->cmd[0], "exit", ft_strlen(sh->cmd_list->cmd[0])) == 0)
		// TODO: Implement good exit
	{
		exit(EXIT_SUCCESS);
	}
	else
		return (1);
	return (0);
}

void	cd(t_sh *sh)
{
	char	cwd[4096];

	chdir(sh->cmd_list->cmd[1]);
	//getcwd(cwd, sizeof(cwd));
	//printf("Current dir : %s", cwd);
	//return (ft_strdup(cwd));
}

void	echo(t_sh *sh)
{
	int	i;

	i = 0;
	if (!sh->cmd_list->cmd[1])
		printf("\n");
	if (ft_strncmp(sh->cmd_list->cmd[1], "-n", 3) == 0)
		i++;
	i++;
	while (sh->cmd_list->cmd[i])
	{
		printf("%s", sh->cmd_list->cmd[i++]);
		if (sh->cmd_list->cmd[i])
			printf(" ");
	}
	if (ft_strncmp(sh->cmd_list->cmd[1], "-n", 3) != 0)
		printf("\n");
	exit (0);
}
/*void	executer_built_in(t_sh *sh)
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
		exec_built_in(sh);
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

}*/

/*
echo con la opción -n.
cd solo con una ruta relativa o absoluta.
pwd sin opciones.
export sin opciones.
unset sin opciones.
env sin opciones o argumentos.
exit sin opciones.
*/
