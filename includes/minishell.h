#ifndef MINISHELL_H
# define MINISHELL_H
// 전역변수 exit_status로 사용하자구

#include "parser.h"

typedef unsigned long		size_t;
typedef int					(*t_lexer_fp)(t_all_data *);
typedef int					(*t_reducer_fp)(t_all_data *);
typedef struct s_cmd		t_cmd;
typedef struct s_element	t_element;

typedef enum e_return_value
{
	RV_ERROR = -1,
	RV_SUCCESS = 0
}	t_return_value;

typedef enum e_lexer_state
{
	LS_OTHERS,
	LS_ITEM,
	LS_SPACE,
	LS_SQUOT,
	LS_DQUOT,
	LS_NULL
}	t_lexer_state;


typedef struct s_node
{
	void			*data;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	size_t	count;
}	t_list;

typedef enum e_item_type
{
	ITEM_SPACE,
	ITEM_TAB,
	ITEM_NL,
	ITEM_PIPE,
	ITEM_AND,
	ITEM_SEMICOL,
	ITEM_LPAREN,
	ITEM_RPAREN,
	ITEM_LESS,
	ITEM_GREATER,
	NOT_ITEM
}	t_item_type;

typedef struct s_env_data
{
	char	*key;
	char	*value;
}	t_env_data;

typedef struct s_token_data
{
	t_token_type	token_type;
	char			*content;
}	t_token_data;

/*                                           */

typedef struct s_lexer
{
	char			*input;
	char			last_item;
	size_t			index;
	t_lexer_state	current_state;
	t_lexer_fp		lex_func[5][5];
}	t_lexer;

typedef struct s_all_data
{
	t_list		envp_list;
	t_list		token_list;
	t_lexer		lexer;
	t_parser	parser;
}	t_all_data;

/* exit.c */
void	exit_with_message(char *s);

/* init_all.c */
void	init_all(t_all_data *all_data, char **envp);

/* lexer_table.c */
t_return_value	get_next_char(t_all_data *all_data);
t_return_value	others_meet_space(t_all_data *all_data);
t_return_value	others_meet_squot(t_all_data *all_data);
t_return_value	others_meet_dquot(t_all_data *all_data);
t_return_value	others_meet_item(t_all_data *all_data);
t_return_value	space_meet_others(t_all_data *all_data);
t_return_value	space_meet_space(t_all_data *all_data);
t_return_value	space_meet_squot(t_all_data *all_data);
t_return_value	space_meet_dquot(t_all_data *all_data);
t_return_value	space_meet_item(t_all_data *all_data);
t_return_value	item_meet_others(t_all_data *all_data);
t_return_value	item_meet_space(t_all_data *all_data);
t_return_value	item_meet_squot(t_all_data *all_data);
t_return_value	item_meet_dquot(t_all_data *all_data);
t_return_value	item_meet_item(t_all_data *all_data);
t_return_value	turn_others(t_all_data *all_data);

/* list_envp.c */
void	print_envp(t_all_data *all_data);
int		envp_search_node(t_list *list, char *key);
void	envp_delete_node(t_list *list, int index);
void	get_envp(t_all_data *all_data, char **envp);
t_env_data	*create_envp_data(char *key, char *value);
void	envp_delete_node(t_list *list, int index);

/* list_stack.c */
void	stack_pop_back(t_list *list, int count);
t_parser_data	*create_parser_data(int type);

/* list_token.c */


/* list.c */ //node_number start from zero
t_node	*list_pop_back(t_list *list);
void	list_push_back(t_list *list, t_node *new);
t_node	*list_new_node(void *data);
void	list_init(t_list *list);

/* parsing.c */
void	check_arguments(int	argc, char **argv);

/* readline.c */
void    prompt_loop(t_all_data *all_data);
void 	handler(int signum);

/* utils_split.c */
char	**ft_split(char const *s, char *set);

/* utils_string.c */
void	*ft_malloc(size_t bytes);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t detsize);


#endif
