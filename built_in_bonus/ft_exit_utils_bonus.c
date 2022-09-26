/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:20:33 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:19:23 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

void	init_atoi(const char *str, \
					int *index, int *plma, unsigned long long *result)
{
	*index = 0;
	while (str[(*index)] == ' ' || (str[(*index)] >= 9 && str[(*index)] <= 13))
		++(*index);
	*plma = 1;
	if (str[(*index)] == '-')
		*plma = -1;
	if (str[(*index)] == '-' || str[(*index)] == '+')
		++(*index);
	*result = 0;
}
