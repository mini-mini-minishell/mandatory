#ifndef MINISHELL_H
# define MINISHELL_H
// 전역변수 exit_status로 사용하자구

# include "typedef.h"
# include "get_next_line.h"

/*---------------------------------*/
/* built_in */

/* ft_cd_utils.c */
int				check_one_word(t_cmd *cmd, const char target);
int				do_replace(t_cmd *cmd, char *pwd, char *key);
int				replace_pwd(char *target, t_cmd *cmd);

/* ft_cd_utils2.c */
t_node			*where_in_envp_list(t_list *envp_list, const char *variable);
char			*find_envp_value(t_list *envp_list, const char *variable);

/* ft_cd.c */
int				ft_cd(t_cmd *cmd);

/* ft_echo.c */
int				ft_echo(t_cmd *cmd);

/* ft_env */
int 			ft_env(t_cmd *cmd);

/*ft_export_envp.c*/
t_node			*envp_search_node_by_key(t_list *list, char *key);
void			envp_delete_node_by_target(t_list *list, t_node **target);
t_node			*cut_and_make_envp_node(char *str);

/*ft_export_utils.c*/
int				isname(char *target);
size_t			isname_get_length(char *target);

/* ft_exit.c */
int				ft_exit(t_cmd *cmd);

/* ft_export.c */
int				ft_export(t_cmd *cmd);

/* ft_pwd.c */
int				ft_pwd(t_cmd *cmd);

/* ft_unset.c */
int				ft_unset(t_cmd *cmd);
// void			delete_target_env_node(t_list *envp_list, char *key); 날림

/*---------------------------------*/

/* execute_command.c */
int				execute_command(t_cmd *cmd, int fd_info[3]);
int				execute_command_internal(t_cmd *cmd, int fd_info[3]);
t_built_in_fp	is_builtin(t_list *word_list);

/* execute_do_redirection.c */
int				do_redirections(int fd_info[3], t_list *redir_list, t_list *env);

/* execute_get_redir_fd.c */
int				get_redir_fd(t_redir_data *redir_data, t_list *envp_list);

/* execute_nonbuiltin.c */
int				execute_nonbuiltin(t_cmd *cmd);
//int				is_directory(char *file);


/* execute_simple.c */
int				execute_simple(t_cmd *cmd, int fd_info[3]);

/* execute_utils.c */
int				save_fd_status(int fd_buff[2]);
int				restore_fd_status(int fd_buff[2], int exit_status);
int				ft_waitchild(t_cmd *cmd);
int				get_exit_status(int status);

/* exit.c */
void			exit_with_message(char *s);

/* ------------------------------- */

/* expand_no_variable.c */
void			no_variable_expansion(char *word, t_expansion_flag flag, \
				t_expansion_info *info);

/* expand_nosplit.c */
int				expand_variable_nosplit(char *value, char *curr_word, t_list **info_new_addr);

/* expand_string.c */
char			*get_expanded_string(t_list *env, char **word, char **name);

/* expand_substitute.c */
void			substitute_filename(t_list **info_new_addr);

/* expand_variable.c */
void			expand_variable(char **word, t_list *env, t_expansion_flag flag, t_expansion_info *info);
void			update_last_node_word(t_list *new_list, char *curr_word);

/* expansion_filename.c */
int				filename_expansion(t_list **info_new_list);

/* expansion_match.c */
int				match(char *pattern, char *name);

/* expansion_one_node.c */
t_list			*expand_one_node(t_node *word, t_list *env, t_expansion_flag flag);

/* expansion_word_list.c */
t_list			*expand_word_list(t_list *words, t_list *env, t_expansion_flag flag);

/* expansion.c */
t_list			*expansion_all(t_list *words, t_list *env);
t_list			*expansion_heredoc_content(t_list *words, t_list *env);

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

/* heredoc.c */
int				gather_heredoc(t_parser *parser);
t_quot_state	check_quote(char word, int quote_flag);

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
void			print_envp(t_list envp_list);
char			*envp_search_value(t_list list, char *key);
void			envp_delete_node(t_list *list, size_t index);
void			get_envp(t_all_data *all_data, char **envp);
t_env_data		*create_envp_data(char *key, char *value);
void			envp_free_node(t_node **node);

/* list_heredoc.c */
void			heredoc_list_remove_head_node(t_heredoc_list *list);
t_heredoc_node	*heredoc_list_pop_back(t_heredoc_list *list);
void			heredoc_list_push_back(t_heredoc_list *list, t_heredoc_node *new);
t_heredoc_node	*heredoc_list_new_node(t_list *data);
void			heredoc_list_init(t_heredoc_list *list);

/* list_stack.c */
void			stack_pop_back(t_list *list, int count);
void			parser_push_back(t_list *list, int type);
void			tree_push_back(t_list *list, t_tree_content content);
t_parser_data	*create_parser_data(int type);
t_tree_data		*create_tree_data(t_tree_content content);

/* list_stack2.c */
t_redir_data	*create_redir_data(void);
t_parser_state	parser_peek_state(t_list parser_stack);
void			redir_push_back(t_parser *parser, t_list *new_redir_list);

/* list_token.c */
void			add_new_token(t_all_data *all_data);
t_item_type		get_item_type(char c);
t_token_data	*create_token_data(t_all_data *all_data);

/* list_trans.c */
char			**trans_envp_list_2_array(t_list envp_list);
char			**trans_word_list_2_array(t_list word_list);

/* list.c */ //node_number start from zero
void			list_remove_head_token(t_list *list);
t_node			*list_pop_head(t_list *list);
t_node			*list_pop_back(t_list *list);
void			list_push_back(t_list *list, t_node *new);
t_node			*list_new_node(void *data);
void			list_init(t_list *list);
void			list_remove_head_word(t_list *list);
void			list_remove_head_redir(t_list *list);
void			word_list_remove_all(t_list *list);

/* make_redir.c */
t_node			*make_redir_node(char *word, t_token_type token);

/* parser.c */
int				parse_and_execute(t_all_data *all_data);

/* parsing.c */
void			check_arguments(int	argc, char **argv);

/* process_line.c */
int				process_line(t_all_data *all_data, char *input);

/* heredoc.c */
int				gather_heredoc(t_parser *parser);

/* readline.c */
void			prompt_loop(t_all_data *all_data);

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

/* reduce_make.c */
t_cmd			*make_simple(t_all_data *all_data, void *simple_data, void *element_data);
t_cmd			*make_connect(t_all_data *all_data, void *left, void *right, void *connector);
t_cmd			*make_subshell(t_all_data *all_data, t_cmd *subshell);

/* reduce_utils.c */
t_word_data		*create_word_data(char *word);
void			append_word_list(t_cmd *new_simple, t_element *element);
void			append_redir_list(t_cmd *new_simple, t_element *element);
t_cmd			*make_new_simple(t_all_data *all_data);

/* run_lexer.c */
t_lexer_state	ft_lexer_state(char c);
int				run_lexer(t_all_data *all_data);

/* run_parser.c */
int				run_parser(t_all_data *all_data);

/* signal_handler.c */
void			set_prompt_handler(int sig);
void			set_handler_for_heredoc(int sig);
void			set_handler_for_default(void);
void			set_handler_for_ignore(void);
 
/* utils_fd.c */
t_pid			ft_fork(void);
int				ft_pipe(int heredoc_fd[2]);
int				ft_close(int fd);
int				ft_dup2(int fd1, int fd2);

/*utils_itoa.c*/
char			*ft_itoa(int n);

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
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t resultsize);
char			*ft_strchr(const char *s, int c);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);


/* test.c */
void			print_token_data(t_all_data *all_data);
void			print_tree_stack(t_list tree_stack);
void			print_word_data(t_list *word_list);

//_______________________________
/* 1.execute_connect */
int				execute_connect(t_cmd *cmd, int fd_info[3]);

/* 1.execute_pipe.c */
int				execute_single_pipe(t_cmd *cmd, int fd_info[3]);
int				execute_pipe(t_cmd *cmd, int fd_info[3]);

/* 1.execute_subshell.c */
int				execute_subshell(t_cmd *cmd, int fd_info[3]);

#endif
