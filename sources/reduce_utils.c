#include "../includes/minishell.h"
#include <stdlib.h>

t_word_data	*create_word_data(char *word)
{
	t_word_data	*new_data;

	new_data = ft_malloc(sizeof(t_word_data));
	new_data->flag = 0;
	new_data->field = 0;
	new_data->key_len = 0;
	//new_data->variables = NULL;
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
	if (redir_list)
	{
		element->redir_list->head->prev = redir_list->tail;
		redir_list->tail->next = element->redir_list->head;
		redir_list->tail = element->redir_list->tail;
	}
	else
	{
		redir_list = element->redir_list;
	}
}

#include <stdio.h>

t_cmd	*make_simple(t_all_data *all_data, void *simple_data, void *element_data)
{
	t_cmd			*new_simple;
	t_tree_data		*simple;
	t_tree_data		*element;

	simple = simple_data;
	element = element_data;
	if (!simple)
	{
		new_simple = ft_malloc(sizeof(t_cmd));
		new_simple->type = CMD_SIMPLE;
		new_simple->flag = CMD_FLAG_DEFAULT;
		new_simple->content.simple.words = NULL;
		new_simple->redir_list = NULL;
		new_simple->envp_list = &all_data->envp_list;
		new_simple->exit_status = 0;
		new_simple->pid_last_child = -1;
	}
	else
		new_simple = simple->content.cmd;
	if (element->content.cmd)
		append_word_list(new_simple, element->content.element);
	else if (element->content.element->redir_list)
		append_redir_list(new_simple, element->content.element);
	return (new_simple);
}

t_cmd	*make_connect(t_all_data *all_data, void *left, void *right, void *connector)
{
	t_cmd		*new_cmd;
	t_tree_data	*l;
	t_tree_data	*r;
	t_tree_data	*c;

	l = left;
	r = right;
	c = connector;
	new_cmd = ft_malloc(sizeof(t_cmd));
	new_cmd->type = CMD_CONNECT;
	new_cmd->flag = CMD_FLAG_DEFAULT;
	new_cmd->content.connect.left = l->content.cmd;
	new_cmd->content.connect.right = r->content.cmd;
	new_cmd->content.connect.token = c->content.token;
	new_cmd->redir_list = NULL;
	new_cmd->envp_list = &all_data->envp_list;
	new_cmd->pid_last_child = -1;
	return (new_cmd);
}

t_cmd	*make_subshell(t_all_data *all_data, t_cmd *subshell)
{
	t_cmd	*new_subshell;

	new_subshell = ft_malloc(sizeof(t_cmd));
	new_subshell->type = CMD_SUBSHELL;
	new_subshell->flag = CMD_FLAG_DEFAULT;
	new_subshell->content.subshell.cmd = subshell;
	new_subshell->redir_list = NULL;
	new_subshell->envp_list = &all_data->envp_list;
	new_subshell->pid_last_child = -1;
	return (new_subshell);
}
