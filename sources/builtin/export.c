

//export [name[=value]]
// Mark each name to be passed to child processes in the environment.
// the names refer to shell variables.
// If no names are supplied, a list of names of all exported variables is
//displayed.
// The return status is zero unless an invalid option is supplied, one of the
//names is not a valid shell variable name

static char	*extract_key(char *target)
{
	char	*result;
	int		idx;
	int		len;

	if (ft_strchr(target, '=') == NULL)
	{
		len = ft_strlen(target) + 1;
	}
	else
	{
		len = ft_strchr(target, '=') - target + 1;
	}
	result = malloc(sizeof(char) * (len));
	idx = 0;
	while (target[idx] != '\0' && target[idx] != '=')
	{
		result[idx] = target[idx];
		idx++;
	}
	result[idx] = '\0';
	return (result);
}

static t_env_list	*find_env_by_key(t_cmd *cmd, t_word_list *curr)
{
	char		*key_extracted;
	t_env_list	*target;

	key_extracted = extract_key(curr->word);
	target = ft_find_env_list(cmd->env, key_extracted);
	free(key_extracted);
	return (target);
}

static int	set_env(t_cmd *cmd, t_word_list *curr)
{
	t_env_list	*target;

	if (isname(curr->word))
	{
		target = find_env_by_key(cmd, curr);
		if (target == NULL)
		{
			cmd->env = addback_env_list(cmd->env, new_env(curr->word));
		}
		else if (ft_strchr(curr->word, '='))
		{
			delete_target_env_node(cmd, target);
			cmd->env = addback_env_list(cmd->env, new_env(curr->word));
		}
		return (EXECUTION_SUCCESS);
	}
	else
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(curr->word, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (EXECUTION_FAILURE);
	}
}

static int	set_envs(t_cmd *cmd, t_word_list *curr)
{
	int	return_value;

	return_value = EXECUTION_SUCCESS;
	while (curr != NULL)
	{
		if (set_env(cmd, curr) == EXECUTION_FAILURE)
		{
			return_value = EXECUTION_FAILURE;
		}
		curr = curr->next;
	}
	return (return_value);
}

int	ft_export(t_cmd *cmd)
{
	t_word_list	*curr;
	t_ex_state	return_value;

	return_value = EXECUTION_SUCCESS;
	if (cmd)
	{
		curr = cmd->content.simple.words;
		if (curr)
		{
			return_value = set_envs(cmd, curr);
		}
		else
		{
			print_env_sort_by(cmd->env, 1);
		}
	}
	return (return_value);
}
