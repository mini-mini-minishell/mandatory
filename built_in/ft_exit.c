#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

extern int	g_exit_status;

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					plma;
	int					index;

	index = 0;
	while (str[index] == ' ' || (str[index] >= 9 && str[index] <= 13))
		index++;
	plma = 1;
	if (str[index] == '-')
		plma = -1;
	if (str[index] == '-' || str[index] == '+')
		index++;
	result = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - '0';
		index++;
	}
	if (result > 9223372036854775807 && plma == 1)
		return (-1);
	else if (result > 9223372036854775808ULL && plma == -1)
		return (0);
	return ((int)result * plma);
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
		words = cmd->content.simple.words->head->data;
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