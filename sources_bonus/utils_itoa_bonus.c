/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_itoa_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:23:05 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:26:30 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

static int	ft_count_dec(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += 1;
		n *= -1;
	}
	while (n / 10 != 0)
	{
		count++;
		n /= 10;
	}
	count++;
	return (count);
}

static void	ft_itoc(char *str, int n, int count)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		str[i] = '-';
		n *= -1;
		i++;
	}
	while (count > i)
	{
		str[count - 1] = (n % 10) + '0';
		n /= 10;
		count --;
	}
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;

	count = ft_count_dec(n);
	str = malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		return (0);
	if (n == -2147483648)
	{
		ft_strlcpy(str, "-2147483648", count + 1);
		return (str);
	}
	ft_itoc(str, n, count);
	str[count] = '\0';
	return (str);
}
