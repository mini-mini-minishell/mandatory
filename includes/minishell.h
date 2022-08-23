#ifndef MINISHELL_H
# define MINISHELL_H
// 전역변수 exit_status로 사용하자구

# include "typedef.h"

/* exit.c */
void			exit_with_message(char *s);

/* goto_func.c */
t_parser_state	goto_from_state_0(t_token_type type);
t_parser_state	goto_from_state_1(t_token_type type);
t_parser_state	goto_from_state_2(t_token_type type);
t_parser_state	goto_from_state_4(t_token_type type);
t_parser_state	goto_from_state_5(t_token_type type);
t_parser_state	goto_from_state_7(t_token_type type);
t_parser_state	goto_from_state_10(t_token_type type);
t_parser_state	goto_from_state_11(t_token_type type);
t_parser_state	goto_from_state_12(t_token_type type);
t_parser_state	goto_from_state_14(t_token_type type);
t_parser_state	goto_from_state_16(t_token_type type);
t_parser_state	goto_from_state_18(t_token_type type);

/* goto_state.c */
t_parser_state	get_goto_state(t_parser_state state, t_token_type type);
int				goto_next_state(t_all_data *all_data, \
								t_parser_state goto_state, t_token_type type);

/* init_all.c */
void			init_all(t_all_data *all_data, char **envp);

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
void			print_envp(t_all_data *all_data);
int				envp_search_node(t_list *list, char *key);
void			envp_delete_node(t_list *list, size_t index);
void			get_envp(t_all_data *all_data, char **envp);
t_env_data		*create_envp_data(char *key, char *value);
void			envp_delete_node(t_list *list, size_t index);

/* list_stack.c */
void			stack_pop_back(t_list *list, int count);
void			parser_push_back(t_list *list, int type);
void			tree_push_back(t_list *list, t_tree_content content);
t_parser_data	*create_parser_data(int type);
t_tree_data		*create_tree_data(t_tree_content content);


/* list_stack2.c */

t_parser_state	parser_peek_state(t_list parser_stack);

/* list_token.c */
void			add_new_token(t_all_data *all_data);
t_item_type		get_item_type(char c);
t_token_data	*create_token_data(t_all_data *all_data);

/* list.c */ //node_number start from zero
void			list_remove_head_token(t_list *list);
t_node			*list_pop_back(t_list *list);
void			list_push_back(t_list *list, t_node *new);
t_node			*list_new_node(void *data);
void			list_init(t_list *list);

/* make_redir.c */
t_list			*make_redir(char *word, t_token_type token);

/* parser.c */
static void		init_parser(t_all_data *all_data);
static int		should_stop_parsing(int *value);
void			parse_and_execute(t_all_data *all_data);


/* parsing.c */
void			check_arguments(int	argc, char **argv);

/* process_line.c */
int				process_line(t_all_data *all_data, char *input);

/* heredoc.c */
int				gather_heredoc(t_parser *parser);

/* readline.c */
void			prompt_loop(t_all_data *all_data);
void			handler(int signum);

/* reduce_func.c */
t_return_value	reduce_rule_0(t_all_data *all_data);
t_return_value	reduce_rule_1(t_all_data *all_data);
t_return_value	reduce_rule_2(t_all_data *all_data);
t_return_value	reduce_rule_3(t_all_data *all_data);
t_return_value	reduce_rule_4(t_all_data *all_data);
t_return_value	reduce_rule_5(t_all_data *all_data);
t_return_value	reduce_rule_6(t_all_data *all_data);
t_return_value	reduce_rule_7(t_all_data *all_data);
t_return_value	reduce_rule_8(t_all_data *all_data);
t_return_value	reduce_rule_9(t_all_data *all_data);
t_return_value	reduce_rule_10(t_all_data *all_data);
t_return_value	reduce_rule_11(t_all_data *all_data);
t_return_value	reduce_rule_12(t_all_data *all_data);
t_return_value	reduce_rule_13(t_all_data *all_data);
t_return_value	reduce_rule_14(t_all_data *all_data);
t_return_value	reduce_rule_15(t_all_data *all_data);

/* run_lexer.c */
t_lexer_state	ft_lexer_state(char c);
int				run_lexer(t_all_data *all_data);

/* run_parser.c */
int	run_parser(t_all_data *all_data);

/* utils_reduce.c */
t_word_data		*create_word_data(char *word);
void			append_word_list(t_cmd *new_simple, t_element *element);
void			append_redir_list(t_cmd *new_simple, t_element *element);
t_cmd			*make_simple(void *simple_data, void *element_data);
t_cmd			*make_connect(void *left, void *right, void *connector);
t_cmd			*make_subshell(t_cmd *subshell);

/* utils_split.c */
char			**ft_split(char const *s, char *set);

/* utils_string.c */
void			*ft_malloc(size_t bytes);
void			ft_putstr_fd(char *s, int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlcpy(char *dst, const char *src, size_t detsize);

/* test.c */
void			print_token_data(t_all_data *all_data);

#endif
