#include "../includes/minishell.h"
#include <stdlib.h>


t_env_list	*ft_find_env_list(t_env_list *env, const char *var_name)
{
	t_env_list	*curr;

	curr = env;
	while (curr != NULL && ft_strcmp(curr->key, var_name) != 0)
	{
		curr = curr->next;
	}
	return (curr);
}

char	*ft_find_variable(t_env_list *env, const char *var_name)
{
	t_env_list	*curr;

	curr = ft_find_env_list(env, var_name);
	if (curr != NULL)
	{
		return (curr->value);
	}
	else
	{
		return (NULL);
	}
}
