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

void	parser_push_back(t_list *list, int type)
{
	void	*data;

	data = create_parser_data(type);
	list_push_back(list, data);
}

void	tree_push_back(t_list *list,)
{}

t_parser_data	*create_parser_data(int type)
{
	t_parser_data	*new_data;

	new_data = ft_malloc(sizeof(t_parser_data));
	if(type & PARSER_STATE)
	{
		new_data->type = PARSER_STATE;
		new_data->state = type;
	}
	else
	{
		new_data->type = 0;
		new_data->token = type;
	}
	return (new_data);
}

