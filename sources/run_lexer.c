#include "../includes/minishell.h"
#include "../includes/parser.h"

int	run_lexer(t_all_data *all_data)
{
	t_lexer			*lexer;
	t_lexer_fp		func;
	t_lexer_state	next_state;
	t_token_data	*token_data;
	char			next_char;

	lexer = &all_data->lexer;
	while (1)
	{
		next_char = (lexer->input)[lexer->index];
		next_state = ft_lexer_state(next_char);
		if (next_state == LS_NULL)
			break ;
		func = lexer->lex_func[lexer->current_state][next_state];
		if (func(lexer) < 0)
			return (-1);
	}
	if (lexer->current_state == LS_SQUOT || lexer->current_state == LS_DQUOT)
		return (-1);
	if (lexer->current_state == LS_ITEM || lexer->current_state == LS_OTHERS)
	{
		add_new_token(all_data);
		token_data = all_data->token_list.tail->data;
		if (token_data->token_type == TT_ERR)
			return (-1);
	}
	return (0);
}
