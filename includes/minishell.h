#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h> //idk if this is used
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/time.h>//debug

typedef struct	s_sh
{
	int				argc; // debugger
	char			**argv; // debugger
	char			**env;
	struct s_cmd	*cmd_list;
	struct s_galloc	*l_galloc;
}	t_sh;

typedef struct	s_cmd
{
	int				cmd_count;
	int				pipes;
	int				f_next_infile;
	int				f_next_outfile;
	char			*infile;
	char			*outfile;
	char			**cmd;
	struct s_cmd	*next;
	struct s_cmd	*start;
}	t_cmd;

typedef struct s_galloc
{
	void			*mem;
	struct s_galloc	*next;
	struct s_galloc	*start;
}	t_galloc;

//utils.c
int	ft_lentoc(const char *str, char c);
//line_finder.c
char	*user_finder(char *user, char *pc, t_sh *sh);
char	*path_finder(char *path, t_sh *sh);
char	*line_finder(t_sh *sh);
//galloc.c
void	terminate(t_sh *sh);
void	free_galloc(t_sh *sh);
void	*add_galloc(void *mem, t_sh *sh);
void	*galloc(size_t size, t_sh *sh);
//parser.c
void	parser(char *input, t_sh *sh);
//execute.h
void	excute(t_sh *sh);

#endif
/* DUDAS
Como reconocer comandos, y < > | u otros simbolos y no confundirlos con comandos,
entiendo que "< infile cmd1 | cm2 > outfile" infile se reconoce por que le precede
< pero no conozco todas las posibilidades ni como de lioso se pues poner

"infile < ls" mal
"< infile cat" bien



*/
