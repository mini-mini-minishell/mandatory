/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:20:38 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/15 13:52:26 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

extern int	g_exit_status;

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					plma;
	int					index;

	init_atoi(str, &index, &plma, &result);
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - '0';
		index++;
	}
	if (result > 9223372036854775807 && plma == 1)
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		return (-1);
	}
	else if (result > 9223372036854775808ULL && plma == -1)
		return (0);
	return ((int)result * plma);
}

static int	are_digit(char *target)
{
	t_size	i;

	i = 0;
	while (target[i] != '\0')
	{
		if (ft_isdigit(target[i]) == 0)
		{
			return (EXECUTION_SUCCESS);
		}
		i++;
	}
	return (EXECUTION_FAILURE);
}

static int	parameter_handling(t_node *word_node, int *exit_status)
{
	t_word_data	*data;

	data = word_node->data;
	if (are_digit(data->word))
	{
		*exit_status = ft_atoi(data->word);
		if (*exit_status > 256)
		{
			*exit_status %= 256;
		}
	}
	else
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		exit(255);
	}
	if (word_node->next != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (EXECUTION_FAILURE);
	}
	return (EXECUTION_SUCCESS);
}

int	ft_exit(t_cmd *cmd)
{
	t_node		*node;
	int			exit_status;

	if (cmd)
	{
		node = cmd->content.simple.words->head;
		if (node)
		{
			if (parameter_handling(node, &exit_status) == EXECUTION_SUCCESS)
			{
				printf("exit\n");
				exit(exit_status);
			}
		}
		else
		{
			printf("exit\n");
			exit(g_exit_status);
		}
	}
	return (EXECUTION_FAILURE);
}
