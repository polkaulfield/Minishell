#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> //idk if this is used
#include <readline/readline.h>
#include <readline/history.h>

typedef struct	s_sh
{
	struct s_galloc	*l_galloc;
}	t_sh;


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
void	free_galloc(t_sh *sh);
void	*add_galloc(void *mem, t_sh *sh);
void	*galloc(size_t size, t_sh *sh);

#endif
