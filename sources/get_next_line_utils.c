#include "../includes/get_next_line.h"

char	*ft_strdup_gnl(const char *s1)
{
	size_t	i;
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

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (src[i])
		i++;
	if (dstsize == 0)
		return (i);
	j = 0;
	while (j < dstsize - 1 && j < i)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = 0;
	return (i);
}

int	ft_no_newline_gnl(char *s)
{
	size_t	i;

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

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

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
	str = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!str)
		return (NULL);
	ft_strlcpy_gnl(str, s1, ft_strlen_gnl(s1) + 1);
	ft_strlcpy_gnl(&str[ft_strlen_gnl(s1)], s2, ft_strlen_gnl(s2) + 1);
	free(s1);
	return (str);
}