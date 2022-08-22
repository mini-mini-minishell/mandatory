#include "../includes/minishell.h"
#include <stdlib.h>

static void	init_parser(t_all_data *all_data)
{
	t_parser		*parser;

	parser = &all_data->parser;
	list_init(&parser->parser_stack);
	list_init(&parser->tree_stack);
	parser->flag = PARSER_ING;
	parser->final_cmd = NULL;
	//parser->heredoc_list = NULL;
	parser_push_back(&parser->parser_stack, STATE_0);
}

void	parse_and_execute(t_all_data *all_data)
{
	t_lexer			*lexer;
	t_parser		parser;
	int				fd_info[3];
	int				return_value;

	lexer = &all_data->lexer;
	init_parser(all_data);
	return_value = 0;
	while (parser.flag == PARSER_ING)
	{
		return_value = run_parser(all_data);
		if (should_stop_parsing(&return_value))
			break ;
	}
	if (parser.flag == PARSER_FINISH)
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
}
