#include "../includes/minishell.h"
#include <stdlib.h>

void	print_envp(t_all_lists *all_lists)
{
	t_list		env;
	t_node		*current_node;
	t_env_data	*current_env;
	int			index;

	env = all_lists->envp_list;
	current_node = env.head;
	index = 0;
	while (index < env.count)
	{
		current_env = (t_env_data *)current_node->data;
		ft_putstr_fd(current_env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(current_env->value, 1);
		ft_putstr_fd("\n", 1);
		current_node = current_node->next;
		++index;
	}
	exit(0); // ---------
}

int	envp_search_node(t_list *list, char *key)
{
	int			index;
	t_node		*current;
	size_t		key_len;
	t_env_data	*temp_data;

	if (!list->count)
		return (-1);
	key_len = ft_strlen(key);
	current = list->head;
	temp_data = (t_env_data *)(current->data);
	index = 0;
	while (index < list->count)
	{
		if (ft_strncmp(key, temp_data->key, key_len + 1))
			return (index);
		current = current->next;
		++index;
	}
	return (-1);
}

static void	get_envp_list(t_list *envp_list, char **envp)
{
	t_node		*new_node;
	int			index;
	char		**current_envp;

	index = 0;
	while(envp[index])
	{
		current_envp = ft_split(envp[index], "=");
		new_node = list_new_node(create_envp_data(current_envp[0], current_envp[1]));
		list_push_back(envp_list, new_node);
		free(current_envp);
		++index;
	}
}

void	get_envp(t_all_lists *all_lists, char **envp)
{
	t_list	*envp_list;

	envp_list = &all_lists->envp_list;
	list_init(envp_list);
	get_envp_list(envp_list, envp);
}
