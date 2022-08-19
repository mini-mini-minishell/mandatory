#include "../includes/minishell.h"
#include <stdio.h>

int gather_heredoc(t_parser *parser)
{
	(void)parser;
	printf("heredoc\n");
	return (1);
}
