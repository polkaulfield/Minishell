#include "../../includes/minishell.h"

int	comand_builder(char *input, t_sh *sh)
{
	//printf("%i\n", sh->cmd_list->cmd_count); //debugger
	if (sh->cmd_list->cmd_count == 0)
	{
		sh->cmd_list->cmd = galloc(10 * sizeof(char *), sh);
		sh->cmd_list->cmd[sh->cmd_list->cmd_count] = ft_strjoin("/bin/", input);
		//necesita buscar la ruta, no debe usar directamente "/bin/"
		add_galloc(sh->cmd_list->cmd[sh->cmd_list->cmd_count], sh);
	}
	else if (input[0] == '-')
	{
		sh->cmd_list->cmd[sh->cmd_list->cmd_count] = ft_strdup(input);
		add_galloc(sh->cmd_list->cmd[sh->cmd_list->cmd_count], sh);
	}
	/*else
	{
	}*/
	sh->cmd_list->cmd_count += 1;
	sh->cmd_list->cmd[sh->cmd_list->cmd_count] = ((void *)0);
	return (0);
}

//comand compare
/*else if (check_built_ins(input, sh))
		NEED IMPLEMENT*/
int	cmd_cmp(char *input, t_sh *sh)
{
//	static int	cmd_parts = 0;
	if (ft_strncmp(input, ">", 2) == 0)
	{
		printf("> founded\n");
		sh->cmd_list->f_next_outfile = 1;
		exit (1);
	}
	else if (ft_strncmp(input, "<", 2) == 0)
	{
		printf("< founded\n");
		sh->cmd_list->f_next_outfile = 1;// tmp solution need check
		exit (1);
	}
	else if (ft_strncmp(input, "|", 2) == 0)
	{
		printf("| founded\n");
		exit(1); // no implmented
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

	sh->cmd_list = galloc(sizeof(t_cmd), sh);
	sh->cmd_list->cmd_count = 0;
	sh->cmd_list->pipes = 0;
	sh->cmd_list->f_next_infile = 0;
	sh->cmd_list->f_next_outfile = 0;
	sh->cmd_list->cmd = NULL;
	sh->cmd_list->infile = NULL;
	sh->cmd_list->outfile = NULL;
	sh->cmd_list->next = NULL;
	sh->cmd_list->start = NULL;
	if (input[0] == '\0')
		return ;
	input_arr = ft_split(input, ' ');
	//if (ft_strncmp(sh->cmd_list->cmd, "", 1) != 0)

	sh->cmd_list->cmd_count = find_cmd(input_arr, sh);
	printf("%s\n", sh->cmd_list->cmd[0]);
	if (sh->cmd_list->cmd)
	{
		excute(sh);
	}
}
