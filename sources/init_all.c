
#include "../includes/minishell.h"
#include <signal.h>

void	set_lexer_table(t_all_data *all_data, t_lexer *lexer)
{
	(lexer->func)[LS_ORDINARY][LS_ORDINARY] = get_next_char;
	(lexer->func)[LS_ORDINARY][LS_SPACE] = ordinary_meet_space;
	(lexer->func)[LS_ORDINARY][LS_SQUOT] = ordinary_meet_squot;
	(lexer->func)[LS_ORDINARY][LS_DQUOT] = ordinary_meet_dquot;
	(lexer->func)[LS_ORDINARY][LS_UNIQUE] = ordinary_meet_unique;
	(lexer->func)[LS_SPACE][LS_ORDINARY] = space_meet_ordinary;
	(lexer->func)[LS_SPACE][LS_SPACE] = space_meet_space;
	(lexer->func)[LS_SPACE][LS_SQUOT] = space_meet_squot;
	(lexer->func)[LS_SPACE][LS_DQUOT] = space_meet_dquot;
	(lexer->func)[LS_SPACE][LS_UNIQUE] = space_meet_unique;
	(lexer->func)[LS_SQUOT][LS_ORDINARY] = get_next_char;
	(lexer->func)[LS_SQUOT][LS_SPACE] = get_next_char;
	(lexer->func)[LS_SQUOT][LS_SQUOT] = meet_ordinary;
	(lexer->func)[LS_SQUOT][LS_DQUOT] = get_next_char;
	(lexer->func)[LS_SQUOT][LS_UNIQUE] = get_next_char;
	(lexer->func)[LS_DQUOT][LS_ORDINARY] = get_next_char;
	(lexer->func)[LS_DQUOT][LS_SPACE] = get_next_char;
	(lexer->func)[LS_DQUOT][LS_SQUOT] = get_next_char;
	(lexer->func)[LS_DQUOT][LS_DQUOT] = meet_ordinary;
	(lexer->func)[LS_DQUOT][LS_UNIQUE] = get_next_char;
	(lexer->func)[LS_UNIQUE][LS_ORDINARY] = unique_meet_ordinary;
	(lexer->func)[LS_UNIQUE][LS_SPACE] = unique_meet_space;
	(lexer->func)[LS_UNIQUE][LS_SQUOT] = unique_meet_squot;
	(lexer->func)[LS_UNIQUE][LS_DQUOT] = unique_meet_dquot;
	(lexer->func)[LS_UNIQUE][LS_UNIQUE] = unique_meet_unique;
}

void	init_all(t_all_data *all_data, char **envp)
{
	set_lexer_table(all_data, &all_data->lexer);
	//init_parsing();
	get_envp(all_data, envp);
	// print_envp(all_data);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}