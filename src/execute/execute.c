#include "../../includes/minishell.h"



void	in_file(t_sh *sh)
{
	if (sh->cmd_list->fd_in_red)
		sh->cmd_list->fd_in = open(sh->cmd_list->infile, O_RDONLY);
	else
		sh->cmd_list->fd_in = open(sh->cmd_list->infile, O_RDONLY);
	if (sh->cmd_list->fd_in < 0)
	{
		printf("infile error\n");
		exit(1);
	}
	dup2(sh->cmd_list->fd_in, STDIN_FILENO);
	close(sh->cmd_list->fd_in);
}

void	out_file(t_sh *sh)
{
	if (sh->cmd_list->fd_out_red)
		sh->cmd_list->fd_out = open(sh->cmd_list->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		sh->cmd_list->fd_out = open(sh->cmd_list->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (sh->cmd_list->fd_out < 0)
	{
		printf("outfile error\n");
		exit(1);
	}
	dup2(sh->cmd_list->fd_out, STDOUT_FILENO);
	close(sh->cmd_list->fd_out);
}

t_cmd	*fork_create(t_sh *sh)
{
	t_cmd	*cmd;

	sh->cmd_list = sh->cmd_list->start;
	cmd = sh->cmd_list;
	while (cmd)
	{
		if (!cmd->main_proces)
		{
			cmd->pid = fork();
			if (!cmd->pid)
				return (cmd);
		}
		cmd = cmd->next;
	}
	return (sh->cmd_list);
}

void	prepare_pipe(t_sh *sh)
{
	t_cmd *cmd;

	if (sh->cmd_list->in_pipe)
		dup2(sh->cmd_list->fd_pipe[0], STDIN_FILENO);
	if (sh->cmd_list->out_pipe)
		dup2(sh->cmd_list->next->fd_pipe[1], STDOUT_FILENO);
	cmd = sh->cmd_list->start;
	while (cmd)
	{
		if (cmd->fd_pipe)
		{
			close(cmd->fd_pipe[0]);
			close(cmd->fd_pipe[1]);
		}
		cmd = cmd->next;
	}
}

//cmd = path_execute(sh->cmd_list->cmd, sh);
	//sh->cmd_list->pid = fork();
void	execute(t_sh *sh)
{
	t_cmd	*temp_cmd;

	execve(sh->cmd_list->cmd[0], sh->cmd_list->cmd, sh->env);
<<<<<<< Updated upstream
	//printf("minishell: Command not Found\n");
	write(2, "minishell: Command not Found\n", 30);
=======
	printf("minishell: Command not Found %s\n", sh->cmd_list->cmd[0]);
>>>>>>> Stashed changes
	exit (1);
}
