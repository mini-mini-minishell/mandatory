
#include "../includes/minishell.h"
#include <signal.h>
#include <stdlib.h>

static void	set_reducer_table(t_parser *parser)
{
	parser->reduce_func[0] = NULL;
	parser->reduce_func[1] = reduce_rule_0;
	parser->reduce_func[2] = reduce_rule_2;
	parser->reduce_func[3] = reduce_rule_4;
	parser->reduce_func[4] = reduce_rule_5;
	parser->reduce_func[5] = reduce_rule_6;
	parser->reduce_func[6] = reduce_rule_9;
	parser->reduce_func[7] = NULL;
	parser->reduce_func[8] = reduce_rule_13;
	parser->reduce_func[9] = reduce_rule_14;
	parser->reduce_func[10] = NULL;
	parser->reduce_func[11] = NULL;
	parser->reduce_func[12] = NULL;
	parser->reduce_func[13] = reduce_rule_8;
	parser->reduce_func[14] = reduce_rule_7;
	parser->reduce_func[15] = reduce_rule_12;
	parser->reduce_func[16] = NULL;
	parser->reduce_func[17] = reduce_rule_15;
	parser->reduce_func[18] = reduce_rule_1;
	parser->reduce_func[19] = reduce_rule_3;
	parser->reduce_func[20] = reduce_rule_11;
	parser->reduce_func[21] = reduce_rule_10;
}

static void	set_lexer_table(t_lexer *lexer)
{
	(lexer->lex_func)[LS_OTHERS][LS_OTHERS] = get_next_char;
	(lexer->lex_func)[LS_OTHERS][LS_SPACE] = others_meet_space;
	(lexer->lex_func)[LS_OTHERS][LS_SQUOT] = others_meet_squot;
	(lexer->lex_func)[LS_OTHERS][LS_DQUOT] = others_meet_dquot;
	(lexer->lex_func)[LS_OTHERS][LS_ITEM] = others_meet_item;
	(lexer->lex_func)[LS_SPACE][LS_OTHERS] = space_meet_others;
	(lexer->lex_func)[LS_SPACE][LS_SPACE] = space_meet_space;
	(lexer->lex_func)[LS_SPACE][LS_SQUOT] = space_meet_squot;
	(lexer->lex_func)[LS_SPACE][LS_DQUOT] = space_meet_dquot;
	(lexer->lex_func)[LS_SPACE][LS_ITEM] = space_meet_item;
	(lexer->lex_func)[LS_SQUOT][LS_OTHERS] = get_next_char;
	(lexer->lex_func)[LS_SQUOT][LS_SPACE] = get_next_char;
	(lexer->lex_func)[LS_SQUOT][LS_SQUOT] = turn_others;
	(lexer->lex_func)[LS_SQUOT][LS_DQUOT] = get_next_char;
	(lexer->lex_func)[LS_SQUOT][LS_ITEM] = get_next_char;
	(lexer->lex_func)[LS_DQUOT][LS_OTHERS] = get_next_char;
	(lexer->lex_func)[LS_DQUOT][LS_SPACE] = get_next_char;
	(lexer->lex_func)[LS_DQUOT][LS_SQUOT] = get_next_char;
	(lexer->lex_func)[LS_DQUOT][LS_DQUOT] = turn_others;
	(lexer->lex_func)[LS_DQUOT][LS_ITEM] = get_next_char;
	(lexer->lex_func)[LS_ITEM][LS_OTHERS] = item_meet_others;
	(lexer->lex_func)[LS_ITEM][LS_SPACE] = item_meet_space;
	(lexer->lex_func)[LS_ITEM][LS_SQUOT] = item_meet_squot;
	(lexer->lex_func)[LS_ITEM][LS_DQUOT] = item_meet_dquot;
	(lexer->lex_func)[LS_ITEM][LS_ITEM] = item_meet_item;
}

void	init_all(t_all_data *all_data, char **envp)
{
	set_lexer_table(&all_data->lexer);
	set_reducer_table(&all_data->parser);
	get_envp(all_data, envp);
	list_init(&all_data->token_list);
	// init_parser(&all_data->parser); //loop 안에서 readline 할때마다 init
	signal(SIGINT, set_prompt_handler);
	signal(SIGQUIT, SIG_IGN);
}
