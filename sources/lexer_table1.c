#include "../includes/minishell.h"

int	ft_get_next_char(t_lexer *lexer)
{
	++(lexer->index);
	return (RV_SUCCESS);
}

int	ft_norm_to_space()