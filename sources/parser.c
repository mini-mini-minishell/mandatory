#include "../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

extern int	g_exit_status;

static void	init_parser(t_all_data *all_data)
{
	t_parser		*parser;

	parser = &all_data->parser;
	list_init(&parser->parser_stack);
	list_init(&parser->tree_stack);
	heredoc_list_init(&parser->heredoc_list);
	parser->flag = PARSER_ING;
	parser->final_cmd = NULL;
	parser_push_back(&parser->parser_stack, STATE_0);
}

static int	should_stop_parsing(int *value)
{
	if (*value == 0)
		return (0);
	if (*value < 0)
	{
		*value = EX_USAGE;
		ft_putstr_fd("syntax error\n", 2);
	}
	return (1);
}

static void	set_final_cmd(t_cmd *cmd, int fd_info[3], t_lexer *lexer)
{
	cmd->exit_status = g_exit_status;
	fd_info[READ_END] = NO_PIPE;
	fd_info[WRITE_END] = NO_PIPE;
	fd_info[CLOSE_END] = NO_PIPE;
}

void	parse_and_execute(t_all_data *all_data)
{
	t_lexer			*lexer;
	t_parser		*parser;
	int				fd_info[3];
	int				return_value;
	t_parser_data	*data;


	lexer = &all_data->lexer;
	parser = &all_data->parser;
	init_parser(all_data);
	return_value = 0;
	while (parser->flag == PARSER_ING)  
	{
		data = all_data->parser.parser_stack.tail->data;
		return_value = run_parser(all_data);
		if (should_stop_parsing(&return_value))
			break ;
	}
	if (parser->flag == PARSER_FINISH)
	{
		set_final_cmd(parser->final_cmd, fd_info, lexer);
		return_value = gather_heredoc(parser);
		if (return_value == 0)
		{
			execute_command(parser->final_cmd, fd_info);
			//return_value = execute_command(parser->final_cmd, fd_info);
			// all_data->envp_list = *parser->final_cmd->envp_list;
		}
	}
	//free_parser(&parser); 아직 안만들었어잉 파서 다 날려야한다.
	// return (return_value);
}
