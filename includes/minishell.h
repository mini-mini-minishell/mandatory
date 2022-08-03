#ifndef MINISHELL_H
# define MINISHELL_H
// 전역변수 exit_status로 사용하자구

typedef unsigned long size_t;

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

/* init_all.c */
void	init_all(t_all_lists *all_lists, char **envp);

/* list_envp.c */
int	envp_search_node(t_list *list, char *key);

/* list.c */ //node_number start from zero
t_node	*list_pop_back(t_list *list);
void	list_push_back(t_list *list, t_node *new);
t_node	*list_new_node(void *data);
void	list_init(t_list *list);


/* parsing.c */
void	check_arguments(int	argc, char **argv);

/* utils_print.c */
void	ft_putstr_fd(char *s, int fd);

/* utils.c */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

#endif