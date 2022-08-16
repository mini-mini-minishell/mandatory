#include "../includes/minishell.h"

t_word_list	*new_word_list(char *word)
{
	t_word_list	*new_list;

	new_list = ft_xmalloc(sizeof(t_word_list));
	new_list->flag = 0;
	new_list->field = 0;
	new_list->key_len = 0;
	new_list->next = NULL;
	new_list->variables = NULL;
	new_list->word = word;
	return (new_list);
}

void	append_word_list(t_cmd *new_simple, t_element *element)
{
	t_list			*word_list;

	word_list = new_simple->content.simple.words;
	if (word_list->count)
	{
		list_push_back(word_list, list_new_node());
		word_list->tail->next = new_word_list(element->word);
	}
	else
	{
		new_simple->content.simple.words = new_word_list(element->word);
	}
}

// void	append_redir_list(t_cmd *new_simple, t_element *element)
// {
// 	t_redir_list	*redir_list;

// 	redir_list = new_simple->redir_list;
// 	if (redir_list)
// 	{
// 		while (redir_list->next)
// 		{
// 			redir_list = redir_list->next;
// 		}
// 		redir_list->next = element->redir_list;
// 	}
// 	else
// 	{
// 		new_simple->redir_list = element->redir_list;
// 	}
// }


t_cmd	*make_simple(void *simple_data, void *element_data)
{
	t_cmd			*new_simple;
	t_tree_data		*simple;
	t_tree_data		*element;

	simple = simple_data;
	element = element_data;
	if (!simple->content.cmd)
	{
		new_simple = ft_malloc(sizeof(t_cmd));
		new_simple->type = CMD_SIMPLE;
		new_simple->flag = CMD_FLAG_DEFAULT;
		new_simple->content.simple.words = NULL;
		new_simple->redir_list = NULL;
		new_simple->envp_list = NULL;
		new_simple->exit_status = 0;
		new_simple->pid_last_child = -1;
	}
	else
		new_simple = simple;
	if (element->content.cmd)
		append_word_list(new_simple, element->content.element);
	else if (element->content.element->redir_list)
		append_redir_list(new_simple, element->content.element);
	return (new_simple);
}

t_cmd	*make_connect(void *left, void *right, void *connector)
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
	new_cmd->envp_list = NULL;
	new_cmd->pid_last_child = -1;
	return (new_cmd);
}