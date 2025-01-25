#include "../../includes/minishell.h"

t_cmd	*cmd_init(t_cmd *cmd_list, t_sh *sh)
{
	cmd_list = galloc(sizeof(t_cmd), sh);
	cmd_list->cmd_count = 0;
	cmd_list->pipes = 0;
	cmd_list->f_next_infile = 0;
	cmd_list->f_next_outfile = 0;
	cmd_list->cmd = NULL;
	cmd_list->infile = NULL;
	cmd_list->outfile = NULL;
	cmd_list->next = NULL;
	cmd_list->start = NULL;
	cmd_list->built_int = 0;
	return (cmd_list);
}
