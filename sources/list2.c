#include "../includes/minishell.h"
#include <stdlib.h>

void	list_remove_head_redir(t_list *list)
{
	t_node			*temp;
	t_redir_data	*data;

	if (!list->count)
		return ;
	temp = list->head;
	data = temp->data;
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
	free(data->file_content);
	free(data->heredoc_eof);
	free(data);
	free(temp);
}

void	list_remove_head_word(t_list *list)
{
	t_node			*temp;
	t_word_data		*data;

	if (!list->count)
		return ;
	temp = list->head;
	data = temp->data;
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
	free(data->word);
	free(data);
	free(temp);
}

void	word_list_remove_all(t_list *list)
{
	while (list->count)
		list_remove_head_word(list);
	free(list);
}