/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:59 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/14 20:21:59 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strdup_gnl(const char *s1)
{
	t_size	i;
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s1) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

t_size	ft_strlcpy_gnl(char *dst, const char *src, t_size detsize)
{
	t_size	i;
	t_size	len;

	i = 0;
	len = ft_strlen_gnl(src);
	if (dst == src || detsize == 0)
		return (len);
	while (i + 1 < detsize && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

int	ft_no_newline_gnl(char *s)
{
	t_size	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

t_size	ft_strlen_gnl(const char *s)
{
	t_size	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;

	if (!s1)
		s1 = ft_strdup_gnl("");
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) \
						*(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!str)
		return (NULL);
	ft_strlcpy_gnl(str, s1, ft_strlen_gnl(s1) + 1);
	ft_strlcpy_gnl(&str[ft_strlen_gnl(s1)], s2, ft_strlen_gnl(s2) + 1);
	free(s1);
	return (str);
}
