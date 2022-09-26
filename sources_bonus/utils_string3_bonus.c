/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:23:12 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:27:00 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, t_size n)
{
	t_size			i;
	unsigned char	*copy1;
	unsigned char	*copy2;

	copy1 = (unsigned char *)s1;
	copy2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (copy1[i] == copy2[i] && copy1[i] != '\0' \
		&& copy2[i] != '\0' && i < n - 1)
		i++;
	return (copy1[i] - copy2[i]);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	t_size	i;
	t_size	size;

	i = 0;
	size = ft_strlen(s);
	copy = ft_malloc(sizeof(char) * size + 1);
	while (i < size)
	{
		copy[i] = s[i];
		i++;
	}
	copy[size] = '\0';
	return (copy);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

char	*ft_strchr(const char *s, int c)
{
	char	char_c;

	char_c = (char)c;
	while (*s != '\0')
	{
		if (*s == char_c)
			return ((char *)s);
		s++;
	}
	if (char_c == '\0')
		return ((char *)s);
	else
		return (NULL);
}

char	*ft_strjoin_free(char *s1, char *s2)
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
	free(s2);
	return (str);
}
