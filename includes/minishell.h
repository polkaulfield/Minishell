#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> //idk if this is used
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_galloc
{
	void			*mem;
	struct s_galloc	*next;
	struct s_galloc	*start;
}	t_galloc;

void	free_galloc(t_galloc *l_galloc);
void	*add_galloc(void *mem, t_galloc *l_galloc);
void	*galloc(size_t size, t_galloc *l_galloc);

#endif
