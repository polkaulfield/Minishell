#include "../includes/minishell.h"

int	main(void)
{
	char		*input;
	char		*line;
	t_sh		*sh;

	int	i = 0; // debugger
	sh = malloc(sizeof(t_sh));
	sh->l_galloc = NULL;
	while(i < 100)
	{
		line = line_finder(sh);
		if (!line)
			line = "?";
		input = readline(line);
		if (!input)
			return (1);
		printf("%s\n", input);
		free(input);
		i++; // debugger
	}
	printf("finish\n");
	free_galloc(sh);
	free(sh);
	return (0);
}
