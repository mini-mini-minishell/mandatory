#include "../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

t_word_data	*create_word_data(char *word)
{
	t_word_data	*new_data;

	new_data = ft_malloc(sizeof(t_word_data));
	new_data->flag = 0;
	new_data->field = 0;
	new_data->key_len = 0;
	new_data->variables = NULL;
	new_data->word = word;
	return (new_data);
}

void	append_word_list(t_cmd *new_simple, t_element *element)
{
	t_list			*word_list;

	word_list = new_simple->content.simple.words;
	if (!word_list)
	{
		word_list = ft_malloc(sizeof(t_list));
		list_init(word_list);
		new_simple->content.simple.words = word_list;
	}
	list_push_back(word_list, list_new_node(create_word_data(element->word)));
}

void	append_redir_list(t_cmd *new_simple, t_element *element)
{
	t_list			*redir_list;

	redir_list = new_simple->redir_list;
	if (redir_list->count)
	{
		element->redir_list->head->prev = redir_list->tail;
		redir_list->tail->next = element->redir_list->head;
		redir_list->tail = element->redir_list->tail;
		new_simple->redir_list = redir_list;
		free(element->redir_list);
	}
	else
		new_simple->redir_list = element->redir_list;
}

t_cmd	*make_new_simple(t_all_data *all_data)
{
	t_cmd	*new_simple;

	new_simple = ft_malloc(sizeof(t_cmd));
	new_simple->type = CMD_SIMPLE;
	new_simple->flag = CMD_FLAG_DEFAULT;
	new_simple->content.simple.words = NULL;
	new_simple->redir_list = ft_malloc(sizeof(t_list));
	list_init(new_simple->redir_list);
	new_simple->envp_list = &all_data->envp_list;
	new_simple->exit_status = 0;
	new_simple->pid_last_child = -1;
	return (new_simple);
}

