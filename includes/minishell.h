#ifndef MINISHELL_H
# define MINISHELL_H
// 전역변수 exit_status로 사용하자구

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

/*                   types                   */
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

typedef enum e_token_type
{
	TT_ERR = 0,
	TT_WORD = 1,
	TT_PAREN_LEFT = 1 << 1,
	TT_PAREN_RIGHT = 1 << 2,
	TT_PIPE = 1 << 3,
	TT_OR = 1 << 4,
	TT_AND = 1 << 5,
	TT_REDIR_IN = 1 << 6,
	TT_REDIR_OUT = 1 << 7,
	TT_REDIR_HEREDOC = 1 << 8,
	TT_REDIR_APPEND = 1 << 9,
	TT_EOF = 1 << 10,
	TT_START = 1 << 11,
	TT_LIST = 1 << 12,
	TT_PIPELINE = 1 << 13,
	TT_CMD = 1 << 14,
	TT_SIMPLE = 1 << 15,
	TT_SUBSHELL = 1 << 16,
	TT_REDIR_LIST = 1 << 17,
	TT_ELEMENT = 1 << 18,
	TT_REDIR = 1 << 19
}	t_token_type;

typedef enum e_tree_type
{
	TREE_TOKEN,
	TREE_WORD,
	TREE_REDIR_LIST,
	TREE_ELEMENT,
	TREE_CMD
}	t_tree_type;

/*                                           */

typedef enum e_parser_state
{
	STATE_NON = 0,
	PARSER_STATE = 1 << 20,
	STATE_0 = PARSER_STATE | 0,
	STATE_1 = PARSER_STATE | 1,
	STATE_2 = PARSER_STATE | 2,
	STATE_3 = PARSER_STATE | 3,
	STATE_4 = PARSER_STATE | 4,
	STATE_5 = PARSER_STATE | 5,
	STATE_6 = PARSER_STATE | 6,
	STATE_7 = PARSER_STATE | 7,
	STATE_8 = PARSER_STATE | 8,
	STATE_9 = PARSER_STATE | 9,
	STATE_10 = PARSER_STATE | 10,
	STATE_11 = PARSER_STATE | 11,
	STATE_12 = PARSER_STATE | 12,
	STATE_13 = PARSER_STATE | 13,
	STATE_14 = PARSER_STATE | 14,
	STATE_15 = PARSER_STATE | 15,
	STATE_16 = PARSER_STATE | 16,
	STATE_17 = PARSER_STATE | 17,
	STATE_18 = PARSER_STATE | 18,
	STATE_19 = PARSER_STATE | 19,
	STATE_20 = PARSER_STATE | 20,
	STATE_21 = PARSER_STATE | 21
}	t_parser_state;

/*                   data                   */

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

typedef struct s_parser_data
{
	int				type;
	t_token_type	token;
	t_parser_state	state;
}	t_parser_data;

typedef struct s_tree_data
{
	int				type;
	t_tree_type		tree_type;
	t_parser_state	state;
	t_token_type	token;
	char			*word;
	t_list			redir_list;
	t_cmd			*cmd;
	t_element		*element;
}	t_tree_data;

/*                                           */

struct s_cmd
{
	t_cmd_flag		flag;
	t_cmd_type		type;
	t_redir_list	*redir_list;
	t_cmd_content	content;
	t_env_list		*env;
	pid_t			pid_last_child;
	int				exit_status;
};

struct s_element
{
	char			*word;
	t_redir_list	*redir_list;
};

typedef struct s_lexer
{
	char			*input;
	char			last_item;
	size_t			index;
	t_lexer_state	current_state;
	t_lexer_fp		lex_func[5][5];
}	t_lexer;

typedef struct s_parser
{
	t_reducer_fp	reduce_func[22];
	t_list			parser_stack;
	t_list			tree_stack; //이름 괜찮은가?
}	t_parser;

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
