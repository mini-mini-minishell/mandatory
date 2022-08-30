#include "../includes/minishell.h"
#include <stdlib.h>


// t_node	*where_in_envp_list(t_list *envp_list, const char *variable)
// {
// 	t_node	*node;

// 	node = envp_list->head;
// 	while (node->next != NULL && ft_strcmp(((t_env_data *)(node->data))->key, variable) != 0)
// 	{
// 		node = node->next;
// 	}
// 	return (node);
// }

char	*find_envp_value(t_list *envp_list, const char *variable)
{
	t_node	*node;

	//node = where_in_envp_list(envp_list, variable);
	if (node != NULL)
		return (((t_env_data *)(node->data))->value);
	else
		return (NULL);
}
