#include "../includes/minishell.h"
#include <stdlib.h>

void	heredoc_list_remove_head_node(t_heredoc_list *list)
{
	t_heredoc_node	*temp;

	if (!list->count)
		return ;
	temp = list->head;
	if (list->count == 1)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		list->head = list->head->next;
		list->head->prev = NULL;
	}
	--(list->count);
	free(temp);
}

t_heredoc_node	*heredoc_list_pop_back(t_heredoc_list *list)
{
	t_heredoc_node	*temp;
	t_heredoc_node	*node;

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
		node = list->tail->prev;
		list->tail = node;
	}
	--(list->count);
	temp->prev = NULL;
	return (temp);
}

void	heredoc_list_push_back(t_heredoc_list *list, t_heredoc_node *new)
{
	if (!list->count)
	{
		list->head = new;
		list->tail = new;
		++(list->count);
		return ;
	}
	new->prev = list->tail;
	list->tail->next = new;
	list->tail = new;
	++(list->count);
}

t_heredoc_node	*heredoc_list_new_node(t_list *data)
{
	t_heredoc_node	*new;

	new = ft_malloc(sizeof(t_heredoc_node));
	new->data = data;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	heredoc_list_init(t_heredoc_list *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;
}
