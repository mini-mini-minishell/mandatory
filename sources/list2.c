#include "../includes/minishell.h"
#include <stdlib.h>

void	list_remove_head_redir(t_list *list)
{
	t_node			*temp;
	t_redir_data	*temp_redir;

	if (!list->count)
		return ;
	temp = list->head;
	temp_redir = temp->data;
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
	free(temp_redir->file_content);
	free(temp_redir->heredoc_eof);
	free(temp_redir);
	free(temp);
}