#include "../includes/minishell.h"

void	free_galloc(t_galloc *l_galloc)
{
	t_galloc	*temp_galloc;
	t_galloc	*list_galloc;

	list_galloc = l_galloc;
	while (list_galloc)
	{
		temp_galloc = list_galloc;
		list_galloc = list_galloc->next;
		if (temp_galloc)
		{
			if (temp_galloc->mem)
				free(temp_galloc->mem);
			free(temp_galloc);
		}
	}
}

void	*add_galloc(void *mem, t_galloc *l_galloc)
{
	t_galloc	*new_node;

	if (!mem)
		return (NULL);
	new_node = malloc(sizeof(t_galloc));
	if (!new_node)
		; // implement terminate();s
	new_node->mem = mem;
	new_node->next = NULL;
	new_node->start = l_galloc->start;
	l_galloc->next = new_node;
	l_galloc = new_node;
	return (mem);
}

void	*galloc(size_t size, t_galloc *l_galloc)
{
	t_galloc	*new_node;
	void		*mem;

	if (!l_galloc)
	{
		l_galloc = malloc(sizeof(t_galloc *));
		if (!l_galloc)
			return (NULL);// check if first galloc fail;
		l_galloc->next = NULL;
		l_galloc->mem = NULL;
		l_galloc->start = l_galloc;
	}
	new_node = malloc(sizeof(t_galloc));
	if (!new_node)
		; // implement terminate();
	mem = malloc(sizeof(size));
	if (!mem)
		; // implement terminate();
	new_node->mem = mem;
	new_node->next = NULL;
	new_node->start = l_galloc->start;
	l_galloc->next = new_node;
	l_galloc = new_node;
	return (mem);
}
