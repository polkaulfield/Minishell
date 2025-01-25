#include "../../includes/minishell.h"

int	comand_builder(char *input, t_sh *sh)
{
	//printf("%i\n", sh->cmd_list->cmd_count); //debugger
	find_built_in(input, sh);
	printf("%i\n", sh->cmd_list->cmd_count);
	// TODO: Get number of parameters
	sh->cmd_list->cmd = galloc(10 * sizeof(char *), sh);
	if (sh->cmd_list->cmd_count == 0 && !sh->cmd_list->built_in)
	{
		sh->cmd_list->cmd[sh->cmd_list->cmd_count] = ft_strjoin("/bin/", input);
		//necesita buscar la ruta, no debe usar directamente "/bin/"
		add_galloc(sh->cmd_list->cmd[sh->cmd_list->cmd_count], sh);
	}
	else
	{
		sh->cmd_list->cmd[sh->cmd_list->cmd_count] = ft_strdup(input);
		add_galloc(sh->cmd_list->cmd[sh->cmd_list->cmd_count], sh);
	}
	return (0);
}

void	check_in_out_file(char *input, t_sh *sh)
{
	if (ft_strncmp(input, "<", 2) == 0)
		sh->cmd_list->f_next_infile = 1;
	else if (ft_strncmp(input, ">", 2) == 0)
		sh->cmd_list->f_next_outfile = 1;
	else if (sh->cmd_list->f_next_infile == 1)
		sh->cmd_list->infile = ft_strdup(input);
	else if (sh->cmd_list->f_next_outfile == 1)
		sh->cmd_list->outfile = ft_strdup(input);
}

//comand compare
int	cmd_cmp(char *input, t_sh *sh)
{
	if (ft_strncmp(input, ">", 2) == 0 || ft_strncmp(input, "<", 2) == 0 \
		|| sh->cmd_list->f_next_infile == 1 || sh->cmd_list->f_next_outfile == 1)
		check_in_out_file(input, sh);
	else if (ft_strncmp(input, "|", 2) == 0)
	{
		printf("| founded\n");// tmp solution need check
		exit (1);
	}
	else if (sh->cmd_list->f_next_infile)
	{
		printf("%i\n", sh->cmd_list->f_next_infile);
		sh->cmd_list->f_next_infile = 0;
		sh->cmd_list->infile = ft_strdup(input);
		add_galloc(sh->cmd_list->infile, sh);
	}
	else if (sh->cmd_list->f_next_outfile)
	{
		printf("%i\n", sh->cmd_list->f_next_outfile);
		sh->cmd_list->f_next_outfile = 0;
		sh->cmd_list->outfile = ft_strdup(input);
		add_galloc(sh->cmd_list->outfile, sh);
	}
	else
	{
		comand_builder(input, sh);
		sh->cmd_list->cmd_count += 1;
		sh->cmd_list->cmd[sh->cmd_list->cmd_count] = ((void *)0);
	}
	return (0);
}

int	find_cmd(char **input_arr, t_sh *sh)
{
	static int	i = -1;

	//i = -1;
	add_galloc(input_arr, sh);
	while (input_arr[++i])
	{
		add_galloc(input_arr[i], sh);
		cmd_cmp(input_arr[i], sh);
	}
	if (!input_arr[i])
		i = -1;
	return (0);
}

void	parser(char *input, t_sh *sh)
{
	char **input_arr;

	sh->cmd_list = cmd_init(sh->cmd_list, sh);
	if (input[0] == '\0')
		return ;
	input_arr = ft_split(input, ' ');
	sh->cmd_list->cmd_count = find_cmd(input_arr, sh);
	//printf("%s\n", sh->cmd_list->cmd[1]); // debug
	// check is a built_in in cmd and make a function for execute that
	printf("Is built in %d\n", sh->cmd_list->built_in);
	if (sh->cmd_list->built_in)
		exec_built_in(input, sh);
	else if (sh->cmd_list->cmd)
		execute(sh);
}
