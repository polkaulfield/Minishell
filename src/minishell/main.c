#include "../../includes/minishell.h"

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        //rl_redisplay();
        readline("Hello>\n");
    }
}

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


	signal(SIGINT, sig_handler);
	while(i < 5) // tmp debugger
	{
		sh->cmd_list = NULL;
		if (env == NULL)
			line = "minishell\n> ";
		else
			line = line_finder(sh);
		input = readline(line);
		if (!input)
			terminate(sh);
		else
			add_history(input);
		add_galloc(input, sh);

		parser(input, sh);
		//free(input);
		i++; // debugger
	}
	//usleep(1000000); // debug
	printf("main\n"); // debug
	terminate (sh);
	return (0);
}
