
#include "../includes/minishell.h"
#include <signal.h>

void	set_lexer_table(t_all_data *all_data, t_lexer *lexer)
{
	(lexer->func)[LS_OTHERS][LS_OTHERS] = get_next_char;
	(lexer->func)[LS_OTHERS][LS_SPACE] = others_meet_space;
	(lexer->func)[LS_OTHERS][LS_SQUOT] = others_meet_squot;
	(lexer->func)[LS_OTHERS][LS_DQUOT] = others_meet_dquot;
	(lexer->func)[LS_OTHERS][LS_ITEM] = others_meet_item;
	(lexer->func)[LS_SPACE][LS_OTHERS] = space_meet_others;
	(lexer->func)[LS_SPACE][LS_SPACE] = space_meet_space;
	(lexer->func)[LS_SPACE][LS_SQUOT] = space_meet_squot;
	(lexer->func)[LS_SPACE][LS_DQUOT] = space_meet_dquot;
	(lexer->func)[LS_SPACE][LS_ITEM] = space_meet_item;
	(lexer->func)[LS_SQUOT][LS_OTHERS] = get_next_char;
	(lexer->func)[LS_SQUOT][LS_SPACE] = get_next_char;
	(lexer->func)[LS_SQUOT][LS_SQUOT] = turn_others;
	(lexer->func)[LS_SQUOT][LS_DQUOT] = get_next_char;
	(lexer->func)[LS_SQUOT][LS_ITEM] = get_next_char;
	(lexer->func)[LS_DQUOT][LS_OTHERS] = get_next_char;
	(lexer->func)[LS_DQUOT][LS_SPACE] = get_next_char;
	(lexer->func)[LS_DQUOT][LS_SQUOT] = get_next_char;
	(lexer->func)[LS_DQUOT][LS_DQUOT] = turn_others;
	(lexer->func)[LS_DQUOT][LS_ITEM] = get_next_char;
	(lexer->func)[LS_ITEM][LS_OTHERS] = item_meet_others;
	(lexer->func)[LS_ITEM][LS_SPACE] = item_meet_space;
	(lexer->func)[LS_ITEM][LS_SQUOT] = item_meet_squot;
	(lexer->func)[LS_ITEM][LS_DQUOT] = item_meet_dquot;
	(lexer->func)[LS_ITEM][LS_ITEM] = item_meet_item;
}

void	init_all(t_all_data *all_data, char **envp)
{
	set_lexer_table(all_data, &all_data->lexer);
	//init_parsing();
	get_envp(all_data, envp);
	list_init(&all_data->token_list);
	// print_envp(all_data);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}