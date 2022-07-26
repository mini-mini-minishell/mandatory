#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define BUFFER_SIZE 1024

char	*ft_strdup_gnl(const char *s1);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);
int		ft_no_newline_gnl(char *buffer);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);

char	*ft_restart_gnl(char *temp);
char	*ft_cut_temp_gnl(char *temp);
char	*ft_read_till_line_gnl(int fd, char *temp);
char	*get_next_line(int fd);

#endif