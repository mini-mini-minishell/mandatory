#include "../includes/minishell.h"

extern int	g_exit_status;

static char	*extract_name(char *target)
{
	size_t	i;
	char	*name;

	i = isname_get_length(target);
	name = NULL;
	if (i > 0)
	{
		name = ft_malloc(sizeof(char) * (i + 1));
		ft_strlcpy(name, target, i + 1);
	}
	return (name);
}

char	*get_expanded_string(t_list *env, char **word, char **name)
{
	char	*value;

	value = NULL;
	if (**word == '?')
	{
		++(*word);
		value = ft_itoa(g_exit_status);
		if (!value)
			exit(2);
	}
	else
	{
		*name = extract_name(*word);
		if (*name)
		{
			*word += ft_strlen(*name);
			value = ft_strdup(envp_search_value(*env, *name));
		}
	}
	return (value);
}
