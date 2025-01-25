#include "../../includes/minishell.h"

void	find_built_in(char *input, t_sh *sh)
{
	if (ft_strncmp(input, "echo", ft_strlen(input)) == 0)
		sh->cmd_list->built_in = 1;
	else if (ft_strncmp(input, "cd", ft_strlen(input)) == 0)
		sh->cmd_list->built_in = 1;
	else if (ft_strncmp(input, "pwd", ft_strlen(input)) == 0)
		sh->cmd_list->built_in = 1;
	else if (ft_strncmp(input, "export", ft_strlen(input)) == 0)
		sh->cmd_list->built_in = 1;
	else if (ft_strncmp(input, "unset", ft_strlen(input)) == 0)
		sh->cmd_list->built_in = 1;
	else if (ft_strncmp(input, "env", ft_strlen(input)) == 0)
		sh->cmd_list->built_in = 1;
	else if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		sh->cmd_list->built_in = 1;
	/*else
		sh->cmd_list->built_in = 0;*/
}

int	exec_built_in(char *input, t_sh *sh)
{
	if (ft_strncmp(input, "echo", ft_strlen(input)) == 0)
		printf("echo\n");
	else if (ft_strncmp(input, "cd", ft_strlen(input)) == 0)
	{
		printf("We are in CD count = %d\n", sh->cmd_list->cmd_count);
		if (sh->cmd_list->cmd_count > 0)
			cd(sh->cmd_list->cmd[1]);
	}
	else if (ft_strncmp(input, "pwd", ft_strlen(input)) == 0)
		printf("pwd\n");
	else if (ft_strncmp(input, "export", ft_strlen(input)) == 0)
		printf("export\n");
	else if (ft_strncmp(input, "unset", ft_strlen(input)) == 0)
		printf("unset\n");
	else if (ft_strncmp(input, "env", ft_strlen(input)) == 0)
		printf("env\n");
	else if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		// TODO: Implement good exit
		exit(EXIT_SUCCESS);
	else
		return (0);
	sh->cmd_list->built_in = 1;
	return (1);
}

char	*cd(char *path)
{
	char	cwd[4096];

	chdir(path);
	getcwd(cwd, sizeof(cwd));
	printf("Current dir : %s", cwd);
	return (ft_strdup(cwd));
}

/*
echo con la opción -n.
cd solo con una ruta relativa o absoluta.
pwd sin opciones.
export sin opciones.
unset sin opciones.
env sin opciones o argumentos.
exit sin opciones.
*/
