#ifndef TYPEDEF_H
# define TYPEDEF_H

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

typedef enum e_parser_flag
{
	PARSER_ING,
	PARSER_FINISH
}	t_parser_flag;

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

typedef enum e_tree_type
{
	TREE_TOKEN,
	TREE_WORD,
	TREE_REDIR_LIST,
	TREE_ELEMENT,
	TREE_CMD
}	t_tree_type;

typedef enum e_cmd_flag
{
	CMD_FLAG_DEFAULT = 0,
	CMD_FLAG_NEED_FORK = 1 << 0,
	CMD_FLAG_IS_FORKED = 1 << 1,
	CMD_FLAG_NEED_PIPE = 1 << 2
}	t_cmd_flag;

typedef enum e_tt_group
{
	TT_CONNECT_GROUP = TT_OR | TT_AND | TT_PIPE,
	TT_REDIR_GROUP = TT_REDIR_IN | TT_REDIR_OUT | \
				TT_REDIR_HEREDOC | TT_REDIR_APPEND
}	t_tt_group;

typedef enum e_action_flag
{
	AF_NON = 0,
	AF_START = TT_EOF,
	AF_LIST = AF_START | TT_AND | TT_OR | TT_PAREN_RIGHT,
	AF_PIPELINE = AF_LIST | TT_PIPE,
	AF_CMD = AF_PIPELINE,
	AF_SIMPLE = AF_CMD | TT_WORD | TT_REDIR_GROUP,
	AF_SUBSHELL = AF_CMD | TT_REDIR_GROUP,
	AF_REDIR_LIST = AF_SUBSHELL,
	AF_ELEMENT = AF_SIMPLE,
	AF_REDIR = AF_SIMPLE
}	t_action_flag;

typedef enum e_cmd_type
{
	CMD_SIMPLE,
	CMD_CONNECT,
	CMD_SUBSHELL
}	t_cmd_type;

typedef enum e_redir_type
{
	REDIR_NON,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND
}	t_redir_type;

typedef unsigned long			size_t;
typedef struct s_all_data		t_all_data;
typedef struct s_lexer			t_lexer;
typedef struct s_parser			t_parser;
typedef t_return_value			(*t_lexer_fp)(t_all_data *all_data);
typedef t_return_value			(*t_reducer_fp)(t_all_data *all_data);
typedef struct s_cmd			t_cmd;
typedef struct s_element		t_element;
typedef int						t_pid;
typedef struct s_env_data		t_env_data;
typedef struct s_token_data		t_token_data;
typedef struct s_node			t_node;
typedef struct s_list			t_list;
typedef struct s_redir_data		t_redir_data;
typedef struct s_simple			t_simple;
typedef struct s_connect		t_connect;
typedef struct s_subshell		t_subshell;
typedef struct s_cmd_content	t_cmd_content;
typedef union u_tree_content	t_tree_content;
typedef struct s_parser_data	t_parser_data;
typedef struct s_tree_data		t_tree_data;
typedef struct s_word_data		t_word_data;

struct s_env_data
{
	char	*key;
	char	*value;
};

struct s_token_data
{
	t_token_type	token_type;
	char			*content;
};

struct s_node
{
	void			*data;
	struct s_node	*prev;
	struct s_node	*next;
};

struct s_list
{
	t_node	*head;
	t_node	*tail;
	size_t	count;
};

struct s_lexer
{
	char			*input;
	char			last_item;
	size_t			index;
	t_lexer_state	current_state;
	t_lexer_fp		lex_func[5][5];
};

struct s_parser
{
	t_reducer_fp	reduce_func[22];
	t_list			parser_stack;
	t_list			tree_stack;
	t_cmd			*final_cmd;
	char			flag;
};

/*
struct s_parser
{
	t_token			*input;
	t_parser_stack	*parser_stack;
	t_value_stack	*value_stack;
	t_heredoc_list	*heredoc_list;
	t_parser_flag	flag;
	t_cmd			*final_cmd;
};
*/

struct s_all_data
{
	t_list		envp_list;
	t_list		token_list;
	t_lexer		lexer;
	t_parser	parser;
};

struct s_redir_data
{
	t_redir_type	redir_type;
	int				flag;
	int				fd_orig;
	int				fd_new;
	char			*filename;
	char			*heredoc_eof;
};

struct s_simple
{
	int				flag;
	t_list			*words;
};

struct s_connect
{
	t_token_type	token;
	t_cmd			*left;
	t_cmd			*right;
};

struct s_subshell
{
	int		flag;
	t_cmd	*cmd;
};

struct s_cmd_content
{
	t_simple	simple;
	t_connect	connect;
	t_subshell	subshell;
};

struct s_cmd
{
	t_cmd_flag		flag;
	t_cmd_type		type;
	t_list			*redir_list;
	t_cmd_content	content;
	t_list			*envp_list;
	t_pid			pid_last_child;
	int				exit_status;
};

struct s_element
{
	char			*word;
	t_list			*redir_list;
};

union u_tree_content
{
	t_token_type	token;
	char			*word;
	t_list			*redir_list;
	t_cmd			*cmd;
	t_element		*element;
};

struct s_parser_data
{
	int				type;
	t_token_type	token;
	t_parser_state	state;
};

struct s_tree_data
{
	int				type;
	t_tree_type		tree_type;
	t_parser_state	state;
	t_tree_content	content;
};

struct s_word_data
{
	int			flag;
	int			key_len;
	int			field;
	char		*word;
	// t_word_data	*variables; // node 일지 ?
};

#endif
