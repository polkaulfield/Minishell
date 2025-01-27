#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	char		*line;
	t_sh		*sh;

	int	i = 0; // debugger
	sh = malloc(sizeof(t_sh));
	sh->l_galloc = NULL;
	sh->argc = argc;
	sh->argv = argv;
	sh->env = env;
	if (argc != 1)
		exit(1);// implement execute the input(**argv) and exit
	while(i < 5) // tmp debugger
	{
		sh->cmd_list = NULL;
		//sh->cmd_list->cmd_count = 0;
		if (env == NULL)
			line = "minishell\n> ";
		else
			line = line_finder(sh);
		//input = NULL;  // debugger
		input = readline(line);
		if (!input)
			terminate(sh);
		parser(input, sh);
		//printf("%s\n", input);
		free(input);
		i++; // debugger
	}
	usleep(1000000);
	printf("main\n");
	terminate (sh);
	return (0);
}
