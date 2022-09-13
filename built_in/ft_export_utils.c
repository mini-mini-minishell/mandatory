#include "../includes/minishell.h"

int	isname(char *target)
{
	int		isname;
	size_t	i;

	isname = 0;
	if (target)
	{
		isname = (ft_isalpha(target[0]) || (target[0] == '_'));
		i = 0;
		while (target[i] && target[i] != '=' && isname)
		{
			isname = (ft_isalnum(target[i]) || target[i] == '_');
			++i;
		}
	}
	return (isname);
}

size_t	isname_get_length(char *target)
{
	int		isname;
	size_t	i;

	isname = 0;
	i = 0;
	if (target)
	{
		isname = (ft_isalpha(target[0]) || (target[0] == '_'));
		while (target[i] && target[i] != '=' && isname)
		{
			++i;
			isname = (ft_isalnum(target[i]) || target[i] == '_');
		}
	}
	return (i);
}
