#include "../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

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
