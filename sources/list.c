#include "../includes/minishell.h"
#include <stdlib.h>

void	list_remove_head_token(t_list *list)
{
	t_node			*temp;
	t_token_data	*temp_token;

	if (!list->count)
		return ;
	temp = list->head;
	temp_token = temp->data;
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
	free(temp_token->content);
	free(temp_token);
	free(temp);
}

t_node	*list_pop_head(t_list *list)
{
	t_node	*temp;

	if (!list->count)
		return (NULL);
	temp = list->head;
	if (list->count == 1)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		list->head = temp->next;
		list->head->prev = NULL;
	}
	temp->next = NULL;
	--(list->count);
	return (temp);
}

t_node	*list_pop_back(t_list *list)
{
	t_node	*temp;
	t_node	*node;

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

void	list_push_back(t_list *list, t_node *new)
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

t_node	*list_new_node(void *data)
{
	t_node	*new;

	new = ft_malloc(sizeof(t_node));
	new->data = data;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
