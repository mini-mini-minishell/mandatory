#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_node
{
	void	*data;
	t_node	*next;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	size_t	count;
}	t_list;

typedef struct s_env_data
{
	char	*key;
	char	*value;
}	t_env_data;

typedef struct s_all_lists
{
	t_list	envp_list;
}	t_all_lists;

/* parsing.c */
void	check_arguments(int	argc, char **argv);

/* utils_print.c */
void	ft_putstr_fd(char *s, int fd);

#endif