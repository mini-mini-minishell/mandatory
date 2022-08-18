#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
//추후 다시 헤더파일 합칠 때 정리..!

typedef struct s_cmd			t_cmd;
typedef int						t_pid;
typedef struct s_list			t_list;

typedef enum e_parser_flag
{
	PARSER_INIT = 1 << 0,
	PARSER_FINISH = 1 << 1
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

typedef struct s_redir_data
{
	t_redir_type	redir_type;
	int				flag;
	int				fd_orig;
	int				fd_new;
	char			*filename;
	char			*heredoc_eof;
}	t_redir_data;

typedef struct s_simple
{
	int				flag;
	t_list			*words;
}	t_simple;

typedef struct s_connect
{
	t_token_type	token;
	t_cmd			*left;
	t_cmd			*right;
}	t_connect;

typedef struct s_subshell
{
	int		flag;
	t_cmd	*cmd;
}	t_subshell;

typedef struct s_cmd_content
{
	t_simple	simple;
	t_connect	connect;
	t_subshell	subshell;
}	t_cmd_content;

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

typedef union u_tree_content
{
	t_token_type	token;
	char			*word;
	t_list			*redir_list;
	t_cmd			*cmd;
	t_element		*element;
}	t_tree_content;

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
	t_tree_content	content;
}	t_tree_data;

typedef struct s_parser
{
	t_reducer_fp	reduce_func[22];
	t_list			parser_stack;
	t_list			tree_stack;
	t_cmd			*final_cmd;
	char			flag;
}	t_parser;

typedef struct s_word_data
{
	int			flag;
	int			key_len;
	int			field;
	char		*word;
	// t_word_data	*variables; // node 일지 ?
}	t_word_data;


#endif
