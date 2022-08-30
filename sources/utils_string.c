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

	if (!s)
		return (0);
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
	dst[i] = 0;
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t resultsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;
	size_t	result;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	i = 0;
	result = dlen + slen;
	if (resultsize <= dlen)
		return (resultsize + slen);
	while (dlen + 1 < resultsize && src[i] != 0)
	{
		dst[dlen++] = src[i++];
	}
	dst[dlen] = '\0';
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	rlen;
	char	*new_str;

	rlen = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(sizeof(char) * (rlen + 1));
	if (new_str == NULL)
		return (0);
	ft_strlcpy(new_str, s1, ft_strlen(s1) + 1);
	ft_strlcat(new_str, s2, rlen + 1);
	return (new_str);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	return (0);
}

static	int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

static	int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if (ft_isupper(c) || ft_islower(c))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
