#include "../includes/minishell.h"

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