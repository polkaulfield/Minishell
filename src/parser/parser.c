#include "../../includes/minishell.h"

int	comand_builder(char *input, t_sh *sh)
{
	//printf("%i\n", sh->cmd_list->cmd_count); //debugger
	//printf("%i\n", sh->cmd_list->cmd_count);
	if (sh->cmd_list->cmd_count == 0)
	{
		sh->cmd_list->cmd = galloc(10 * sizeof(char *), sh);
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
	else if (ft_strncmp(input, "<<", 3) == 0)
		sh->cmd_list->f_next_infile = 2;
	else if (ft_strncmp(input, ">", 2) == 0)
		sh->cmd_list->f_next_outfile = 1;
	else if (ft_strncmp(input, ">>", 3) == 0)
		sh->cmd_list->f_next_outfile = 2;
	else if (sh->cmd_list->f_next_infile > 0)
	{
		if (sh->cmd_list->f_next_infile == 2)
			sh->cmd_list->fd_in_red = 1;
		sh->cmd_list->f_next_infile = 0;
		sh->cmd_list->infile = ft_strdup(input);
		add_galloc(sh->cmd_list->infile, sh);
	}
	else if (sh->cmd_list->f_next_outfile > 0)
	{
		if (sh->cmd_list->f_next_outfile == 2)
			sh->cmd_list->fd_out_red = 1;
		sh->cmd_list->f_next_outfile = 0;
		sh->cmd_list->outfile = ft_strdup(input);
		add_galloc(sh->cmd_list->outfile, sh);
	}
}

//comand compare
int	cmd_cmp(char *input, t_sh *sh)
{
	int	fd_pipe[2];
	if (ft_strncmp(input, ">", 2) == 0 || ft_strncmp(input, "<", 2) == 0 \
		|| ft_strncmp(input, ">>", 3) == 0 || ft_strncmp(input, "<<", 3) == 0 \
		|| sh->cmd_list->f_next_infile > 0 || sh->cmd_list->f_next_outfile > 0)
		check_in_out_file(input, sh);
	else if (ft_strncmp(input, "|", 2) == 0)
	{
		sh->cmd_list->out_pipe = 1;
		cmd_addnode(sh);
		if (pipe(fd_pipe) < 0) //TODO:hay que revisar si esto falla que hay que hacer
			printf("error\n");
		sh->cmd_list->in_pipe = 1;
		sh->cmd_list->fd_pipe = galloc(2 * sizeof(int), sh);
		sh->cmd_list->fd_pipe[0] = fd_pipe[0];
		sh->cmd_list->fd_pipe[1] = fd_pipe[1];
	}
/*	else if (sh->cmd_list->f_next_infile)
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
		}*/
	else
	{
		if (!find_built_int(input, sh))
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
	sh->cmd_list->start = sh->cmd_list;
	if (input[0] == '\0')
		return ;
	input_arr = ft_split(input, ' ');
	sh->cmd_list->cmd_count = find_cmd(input_arr, sh);
	//sh->cmd_list = sh->cmd_list->start; // movido a fork create

	//printf("%s\n", sh->cmd_list->cmd[1]); // debug
	// check is a built_int in cmd and make a function for execute that
	if (sh->cmd_list->cmd)
	{
		sh->cmd_list = fork_create(sh);
		excute(sh);
	}
}
