#include "../includes/minishell.h"
#include <stdlib.h>

void	print_envp(t_list envp_list)
{
	t_node		*current_node;
	t_env_data	*current_env;
	size_t		index;

	current_node = envp_list.head;
	index = 0;
	while (index < envp_list.count)
	{
		current_env = (t_env_data *)current_node->data;
		ft_putstr_fd(current_env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(current_env->value, 1);
		ft_putstr_fd("\n", 1);
		current_node = current_node->next;
		++index;
	}
	// exit(0); // ---------
}

// int	envp_search_node(t_list *list, char *key)
// {
// 	size_t		index;
// 	t_node		*current;
// 	size_t		key_len;
// 	t_env_data	*temp_data;

// 	if (!list->count)
// 		return (-1);
// 	key_len = ft_strlen(key);
// 	current = list->head;
// 	temp_data = (t_env_data *)(current->data);
// 	index = 0;
// 	while (index < list->count)
// 	{
// 		if (ft_strncmp(key, temp_data->key, key_len + 1))
// 			return (index);
// 		current = current->next;
// 		++index;
// 	}
// 	return (-1);
// }


char	*envp_search_value(t_list list, char *key)
{
	size_t		index;
	t_node		*current;
	size_t		key_len;
	t_env_data	*temp_data;

	if (!list.count)
		return (NULL);
	key_len = ft_strlen(key);
	current = list.head;
	index = 0;
	while (index < list.count)
	{
		temp_data = (t_env_data *)(current->data);
		if (!ft_strncmp(key, temp_data->key, key_len + 1))
			return (temp_data->value);
		current = current->next;
		++index;
	}
	return (NULL);
}

static void	get_envp_list(t_list *envp_list, char **envp)
{
	t_node		*new_node;
	int			index;
	char		**current_envp;

	index = 0;
	while (envp[index])
	{
		current_envp = ft_split(envp[index], "=");
		new_node = list_new_node(create_envp_data(current_envp[0], current_envp[1]));
		list_push_back(envp_list, new_node);
		free(current_envp);
		++index;
	}
}

void	get_envp(t_all_data *all_data, char **envp)
{
	t_list	*envp_list;

	envp_list = &all_data->envp_list;
	list_init(envp_list);
	get_envp_list(envp_list, envp);
}
