t_node	*envp_search_node_by_key(t_list *list, char *key)
{
	size_t		index;
	t_node		*current;
	size_t		key_len;
	t_env_data	*temp_data;

	if (!list->count)
		return (-1);
	key_len = ft_strlen(key);
	current = list->head;
	index = 0;
	while (index < list->count)
	{
		temp_data = (t_env_data *)(current->data);
		if (ft_strncmp(key, temp_data->key, key_len + 1))
			return (current);
		current = current->next;
		++index;
	}
	return (NULL);
}

void	envp_delete_node_by_target(t_list *list, t_node **target)
{
	t_node		*temp;

	if (list->count == 1)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else if (list->head == target)
		list->head = (*target)->next;
	else if (list->tail == target)
		list->head = (*target)->prev;
	else
	{	
		(*target)->prev->next = (*target)->next;
		(*target)->next->prev = (*target)->prev;
	}
	--(list->count);
	envp_free_node(target);
}

static void	envp_free_node(t_node **node)
{
	t_env_data	*temp_data;

	temp_data = (t_env_data *)((*node)->data);
	free(temp_data->key);
	free(temp_data->value);
	free(temp_data);
	free(*node);
}

t_node		*cut_and_make_envp_node(char *str)
{
	t_node		*new_node;
	t_env_data	*data;
	char		*cut_point;
	char		*key;
	char		*value;

	new_node = ft_malloc(sizeof(t_node *));
	cut_point = ft_strchr(str, '=');
	if (cut_point)
	{
		key = ft_malloc(sizeof(char) * (cut_point - str + 1));
		ft_strlcpy(key, str, cut_point - str + 1);
		value = ft_malloc(sizeof(char) * (ft_strlen(cut_point)));
		ft_strlcpy(value, cut_point + 1, ft_strlen(cut_point));
	}
	else
	{
		key = ft_malloc(sizeof(char) *ft_strlen(str) + 1);
		ft_strlcpy(key, str, ft_strlen(str) + 1);
		value = NULL;
	}
	data = create_envp_data(key, value);
	new_node->data = data;
	return (new_node);
}