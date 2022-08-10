#include "../includes/minishell.h"
#include <stdlib.h>

t_node	*list_pop_back(t_list *list)
{
	t_node	*temp;
	t_node	*node;
	int		i;

	if (!list->count)
		return (NULL);
	temp = list->tail;
	if (list->count == 1)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		node = list->head;
		i = 0;
		while (i < list->count - 1)
		{
			node = node->next;
			++i;
		}
		list->tail = node;
	}
	--(list->count);
	return (temp);
}

void	list_push_back(t_list *list, t_node *new)
{
	if (!list->count)
	{
		list->head = new;
		list->tail = new;
		++(list->count);
		return ;
	}
	list->tail->next = new;
	list->tail = new;
	++(list->count);
}

t_node	*list_new_node(void *data)
{
	t_node	*new;

	new = ft_malloc(sizeof(t_node));
	new->data = data;
	new->next = NULL;
	return (new);
}

void	list_init(t_list *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;
}