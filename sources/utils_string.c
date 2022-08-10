#include "../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	*ft_malloc(size_t bytes)
{
	void	*return_value;

	return_value = malloc(bytes);
	if (!return_value)
		exit_with_message("Memory Error");
	return (return_value);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
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
	size_t	i;
	size_t	size;

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	slen;

	slen = ft_strlen(s);
	if (start >= slen)
		len = 0;
	substr = ft_malloc(sizeof(char) * (len + 1));
	if (start >= slen)
	{
		ft_strlcpy(substr, "", 1);
		return (substr);
	}
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t detsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
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
