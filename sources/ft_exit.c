#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

extern int	g_exit_status;

static int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

static int	are_digit(char *target)
{
	size_t	i;

	i = 0;
	while (target[i] != '\0')
	{
		if (ft_isdigit(target[i]) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static int	parameter_handling(t_word_data *words, int *exit_status)
{
	if (are_digit(words->word))
	{
		*exit_status = ft_atoi(words->word);
		if (*exit_status > 256)
		{
			*exit_status %= 256;
		}
	}
	else
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(2);
	}
	if (words->word != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	ft_exit(t_cmd *cmd)
{
	t_word_data	*words;
	int exit_status;

	if(cmd)
	{
		words = cmd->content.simple.words;
		if (words)
		{
			if (parameter_handling(words, &exit_status) == EXECUTION_SUCCESS)
			{
				ft_putstr_fd("exit\n", 2);
				exit(exit_status);
			}
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			exit(g_exit_status);
		}
	}
	return (1);
}