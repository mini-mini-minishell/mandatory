
#include "../includes/minishell.h"
#include <signal.h>

void	set_lexer_table(t_lexer *lexer)
{
	(lexer->func)[LS_ORDINARY][LS_ORDINARY] = ft_get_next_char;
	(lexer->func)[LS_ORDINARY][LS_SPACE] = ft_norm_to_space;
	(lexer->func)[LS_ORDINARY][LS_SQUOT] = ft_norm_to_squot;
	(lexer->func)[LS_ORDINARY][LS_DQUOT] = ft_norm_to_dquot;
	(lexer->func)[LS_ORDINARY][LS_UNIQUE] = ft_norm_to_unique;
	(lexer->func)[LS_SPACE][LS_ORDINARY] = ft_space_to_norm;
	(lexer->func)[LS_SPACE][LS_SPACE] = ft_space_to_space;
	(lexer->func)[LS_SPACE][LS_SQUOT] = ft_space_to_squot;
	(lexer->func)[LS_SPACE][LS_DQUOT] = ft_space_to_dquot;
	(lexer->func)[LS_SPACE][LS_UNIQUE] = ft_space_to_unique;
	(lexer->func)[LS_SQUOT][LS_ORDINARY] = ft_get_next_char;
	(lexer->func)[LS_SQUOT][LS_SPACE] = ft_get_next_char;
	(lexer->func)[LS_SQUOT][LS_SQUOT] = ft_to_ordinary;
	(lexer->func)[LS_SQUOT][LS_DQUOT] = ft_get_next_char;
	(lexer->func)[LS_SQUOT][LS_UNIQUE] = ft_get_next_char;
	(lexer->func)[LS_DQUOT][LS_ORDINARY] = ft_get_next_char;
	(lexer->func)[LS_DQUOT][LS_SPACE] = ft_get_next_char;
	(lexer->func)[LS_DQUOT][LS_SQUOT] = ft_get_next_char;
	(lexer->func)[LS_DQUOT][LS_DQUOT] = ft_to_ordinary;
	(lexer->func)[LS_DQUOT][LS_UNIQUE] = ft_get_next_char;
	(lexer->func)[LS_UNIQUE][LS_ORDINARY] = ft_unique_to_norm;
	(lexer->func)[LS_UNIQUE][LS_SPACE] = ft_unique_to_space;
	(lexer->func)[LS_UNIQUE][LS_SQUOT] = ft_unique_to_squot;
	(lexer->func)[LS_UNIQUE][LS_DQUOT] = ft_unique_to_dquot;
	(lexer->func)[LS_UNIQUE][LS_UNIQUE] = ft_unique_to_unique;
}

void	init_all(t_all_data *all_data, char **envp)
{
	set_lexer_table(&all_data->lexer);
	//init_parsing();
	get_envp(all_data, envp);
	// print_envp(all_data);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}