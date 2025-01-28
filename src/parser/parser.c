#include "../../includes/minishell.h"

int	comand_builder(char *input, t_sh *sh)
{
	//printf("%i\n", sh->cmd_list->cmd_count); //debugger
	find_built_in(input, sh);

	if (sh->cmd_list->cmd_count == 0)
	{
		sh->cmd_list->cmd = galloc(10 * sizeof(char *), sh);
		if (sh->cmd_list->built_in)
		{
			sh->cmd_list->cmd[sh->cmd_list->cmd_count] = ft_strdup(input);
		}
		else
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
	else
	{
		comand_builder(input, sh);
		sh->cmd_list->cmd_count += 1;
		sh->cmd_list->cmd[sh->cmd_list->cmd_count] = ((void *)0);
	}
	return (0);
}

void	find_cmd(char **input_arr, t_sh *sh)
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
}

void	parser(char *input, t_sh *sh)
{
	char **input_arr;
	t_cmd	*temp_cmd;

	sh->cmd_list = cmd_init(sh->cmd_list, sh);
	sh->cmd_list->start = sh->cmd_list;
	if (input[0] == '\0')
		return ;
	input_arr = ft_split(input, ' ');
	find_cmd(input_arr, sh);
	//sh->cmd_list = sh->cmd_list->start; // movido a fork create

	//printf("%s\n", sh->cmd_list->cmd[1]); // debug
	// check is a built_int in cmd and make a function for execute that
	//sh->cmd_list = fork_create(sh);
	// TODO revisar essto, hay que usar subprocesos con builtins

	//TODO separa a dos funciones distintas lo siguiente
	sh->cmd_list = fork_create(sh);
	// Subprocess
	if (sh->cmd_list->pid == -1 && !sh->cmd_list->main_proces)
	{
		printf("Fork Error\n");
		exit(1); // TODO revisar si debe ser terminate o exit para el subproceso
	}
	else if (sh->cmd_list->pid == 0 && !sh->cmd_list->main_proces)
	{
		if (sh->cmd_list->infile)
			in_file(sh);
		if (sh->cmd_list->outfile)
			out_file(sh);
		prepare_pipe(sh);
		if (sh->cmd_list->built_in)
			exec_built_in(sh);
		if (sh->cmd_list->cmd)
			execute(sh);
	}
	// Main process
	sh->cmd_list = sh->cmd_list->start;
	temp_cmd = sh->cmd_list;
	while (temp_cmd)
	{
		if (temp_cmd->main_proces) // no estoy seguro de si esto se tiene que hacer asi
		{
			if (sh->cmd_list->infile)
				in_file(sh);
			if (sh->cmd_list->outfile)
				out_file(sh);
			prepare_pipe(sh);
			exec_built_in(sh);
		}
		temp_cmd = temp_cmd->next;
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
