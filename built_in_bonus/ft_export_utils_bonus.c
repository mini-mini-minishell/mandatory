/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:20:43 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:19:31 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

int	isname(char *target)
{
	int		isname;
	t_size	i;

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

t_size	isname_get_length(char *target)
{
	int		isname;
	t_size	i;

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
