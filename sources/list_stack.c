#include "../includes/minishell.h"

void	stack_pop_back(t_list *list, int count)
{
	t_node	*temp;
	int		i;

	i = 0;
	while (i < count)
	{
		temp = list_pop_back(list);
		//free(temp->data); -->노드 내 데이터'들'도 할당 해제
		free(temp);
		++i;
	}
}

// t_node	*create_parser_node()