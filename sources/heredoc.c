#include "../includes/minishell.h"
#include <stdio.h>

int gather_heredoc(t_parser *parser)
{
	(void)parser;
	printf("heredoc\n");
	return (1);
}
/* 
int	gather_heredoc(t_parser *parser)
{
	int				fildes[2];
	int				exit_status;
	t_heredoc_list	*heredoc_list;

	exit_status = 0;
	while (parser->heredoc_list)
	{
		safe_pipe(fildes);
		exit_status = fork_receive_heredoc(parser, fildes);
		if (exit_status != 0)
			break ;
	}
	while (parser->heredoc_list)
	{
		heredoc_list = parser->heredoc_list;
		parser->heredoc_list = heredoc_list->next;
		free(heredoc_list);
	}
	return (exit_status);
}
 */