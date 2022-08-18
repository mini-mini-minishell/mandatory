#include "../includes/minishell.h"

/* void	parse_and_execute(t_all_data *all_data)
{
	t_parser		parser;
	int				fd_info[3];
	int				return_value;

	init_parser(&parser, lexer->token_head);
	return_value = 0;
	while (!(parser.flag & PARSER_FINISH))
	{
		return_value = run_parser(&parser, lexer->table);
		if (should_stop_parsing(&return_value))
			break ;
	}
	if (parser.flag & PARSER_FINISH)
	{
		set_final_cmd(parser.final_cmd, fd_info, lexer);
		return_value = gather_heredoc(&parser);
		if (return_value == 0)
		{
			return_value = execute_command(parser.final_cmd, fd_info);
			lexer->env_list = parser.final_cmd->env;
		}
	}
	free_parser(&parser);
	return (return_value);
} */

static t_lexer	*init_lexer(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->current_state = ft_lexer_state(*input);
	if (lexer->current_state == LS_ITEM)
		lexer->last_item = *input;
	else
		lexer->last_item = '\0';
	lexer->index = 1;
	return (lexer);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++
int	process_line(t_all_data *all_data, char *input)
{
	// int	return_value;

	if (!(*input))
		return (0);
	add_history(input);
	init_lexer(&all_data->lexer, input);
	list_init(&all_data->token_list);
	if (run_lexer(all_data) < 0)
	{
		ft_putstr_fd("Syntax Error\n", 2);
		//' or " 하나만 썼을 경우 등 에러 케이스 나누기?
		// return_value = EX_USAGE;
	}
	print_token_data(all_data);
	// else if (!(all_data->token_list.head))
	// {
	// 	// return_value = 0;
	// }
	// else
	// {
	// 	/* return_value =  */parse_and_execute(all_data);
	// }
	// // free_token(&(all_data->token_list.head));
	// //함수 만들어야 함(우린 list를 프리해도 됨)
	// // return (return_value);
	return (0);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
