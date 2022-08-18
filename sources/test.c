#include "../includes/minishell.h"
#include <stdlib.h>

void	print_token_data(t_all_data *all_data)
{
	t_list			token_list;
	t_node			*current_node;
	t_token_data	*token_data;
	int				index;

	token_list = all_data->token_list;
	current_node = token_list.tail;
	index = 0;
	while (index < token_list.count)
	{
		token_data = (t_token_data *)current_node->data;
		ft_putstr_fd(token_data->content, 1);
		ft_putstr_fd(", ", 1);
		ft_putstr_fd(token_data->token_type, 1);
		ft_putstr_fd("\n", 1);
		current_node = current_node->prev;
		++index;
	}
	exit(0); // ---------
}
