#include "../includes/get_next_line.h"

char	*ft_restart_gnl(char *temp)
{
	t_size	i;
	t_size	len;
	char	*str;

	len = ft_strlen_gnl(temp);
	i = 0;
	while (temp[i] && (temp[i] != '\n'))
		i++;
	if (!temp[i])
	{
		free(temp);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (len - i));
	if (!str)
		return (NULL);
	ft_strlcpy_gnl(str, &temp[i + 1], len - i);
	free(temp);
	return (str);
}

char	*ft_cut_temp_gnl(char *temp)
{
	t_size	i;
	char	*line;

	if (!temp[0])
		return (NULL);
	i = 0;
	while ((temp[i] != '\n') && temp[i])
		i++;
	line = (char *)calloc((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy_gnl(line, temp, i + 2);
	return (line);
}

char	*ft_read_till_line_gnl(int fd, char *temp)
{
	char	*buffer;
	st_size	n;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	n = 1;
	while (n && ft_no_newline_gnl(temp))
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[n] = 0;
		temp = ft_strjoin_gnl(temp, buffer);
	}
	free(buffer);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp[512];
	char		*line;

	if (fd < 0 || fd > 511 || BUFFER_SIZE <= 0)
		return (NULL);
	temp[fd] = ft_read_till_line_gnl(fd, temp[fd]);
	if (!temp[fd])
		return (NULL);
	line = ft_cut_temp_gnl(temp[fd]);
	temp[fd] = ft_restart_gnl(temp[fd]);
	return (line);
}
