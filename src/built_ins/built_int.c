#include "../../includes/minishell.h"

//void	echo_built_int()

int	find_built_int(char *input, t_sh *sh)
{
	if (ft_strncmp(input, "echo", ft_strlen(input)) == 0)
		printf("echo\n");
	else if (ft_strncmp(input, "cd", ft_strlen(input)) == 0)
		printf("cd\n");
	else if (ft_strncmp(input, "pwd", ft_strlen(input)) == 0)
		printf("pwd\n");
	else if (ft_strncmp(input, "export", ft_strlen(input)) == 0)
		printf("export\n");
	else if (ft_strncmp(input, "unset", ft_strlen(input)) == 0)
		printf("unset\n");
	else if (ft_strncmp(input, "env", ft_strlen(input)) == 0)
		printf("env\n");
	else if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		printf("exit\n");
	else
		return (0);
	sh->cmd_list->built_int = 1;
	return (1);
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
