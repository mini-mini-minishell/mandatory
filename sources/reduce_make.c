#include "../includes/minishell.h"

t_cmd	*make_simple(t_all_data *all_data, void *simple_data, void *element_data)
{
	t_tree_data		*data;
	t_cmd			*new_simple;
	t_cmd			*simple;
	t_element		*element;

	simple = NULL;
	data = simple_data;
	if (simple_data)
		simple = data->content.cmd;
	data = element_data;
	element = data->content.element;
	if (!simple)
		new_simple = make_new_simple(all_data);
	else
		new_simple = simple;
	if (element->word)
		append_word_list(new_simple, element);
	else if (element->redir_list)
		append_redir_list(new_simple, element);
	return (new_simple);
}

t_cmd	*make_connect(t_all_data *all_data, void *left, void *right, void *connector)
{
	t_tree_data		*data;
	t_cmd			*new_cmd;
	t_cmd			*l;
	t_cmd			*r;
	t_token_type	c;

	data = left;
	l = data->content.cmd;
	data = right;
	r = data->content.cmd;
	data = connector;
	c = data->content.token;
	new_cmd = ft_malloc(sizeof(t_cmd));
	new_cmd->type = CMD_CONNECT;
	new_cmd->content.connect.left = l;
	new_cmd->content.connect.right = r;
	new_cmd->content.connect.token = c;
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
