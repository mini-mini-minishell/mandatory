#include "../includes/minishell.h"

t_parser_state	get_goto_state(t_parser_state state, t_token_type type)
{
	if (state == STATE_0)
		return (goto_from_state_0(type));
	if (state == STATE_1)
		return (goto_from_state_1(type));
	if (state == STATE_2)
		return (goto_from_state_2(type));
	if (state == STATE_4)
		return (goto_from_state_4(type));
	if (state == STATE_5)
		return (goto_from_state_5(type));
	if (state == STATE_7)
		return (goto_from_state_7(type));
	if (state == STATE_10)
		return (goto_from_state_10(type));
	if (state == STATE_11)
		return (goto_from_state_11(type));
	if (state == STATE_12)
		return (goto_from_state_12(type));
	if (state == STATE_14)
		return (goto_from_state_14(type));
	if (state == STATE_16)
		return (goto_from_state_16(type));
	if (state == STATE_18)
		return (goto_from_state_18(type));
	return (STATE_NON);
}

// struct s_tree_data
// {
// 	int				type;
// 	t_tree_type		tree_type;
// 	t_parser_state	state;ㅇ
// 	t_tree_content	content;
// };

// struct s_parser_data
// {
// 	int				type;
// 	t_token_type	token;
// 	t_parser_state	state;
// };

// union u_tree_content
// {
// 	t_token_type	token;
// 	char			*word;
// 	t_list			*redir_list;
// 	t_cmd			*cmd;
// 	t_element		*element;
// };

// struct s_token_data
// {
// 	t_token_type	token_type;
// 	char			*content;
// };


t_tree_content	get_input_value(t_list *input)
{
	t_token_data	*data;
	t_tree_content	content;

	data = input->head->data;
	if (data->token_type == TT_WORD)
		content.word = ft_strdup(data->content);
	else
		content.token = data->token_type;
	return (content);
}
#include <stdio.h>

int	goto_next_state(t_all_data *all_data, \
					t_parser_state goto_state, t_token_type type)
{
	t_tree_content	content;
	t_token_data	*token_data;
	t_tree_data		*tree_data;

	if (goto_state)
	{
		if (type < TT_START)
		{
			parser_push_back(&all_data->parser.parser_stack, type);
			content = get_input_value(&all_data->token_list);
			tree_push_back(&all_data->parser.tree_stack, content);
			token_data = all_data->token_list.head->data;
			tree_data = all_data->parser.tree_stack.tail->data;
			if (token_data->token_type == TT_WORD)
			{
				tree_data->tree_type = TREE_WORD;
			}
			else
				tree_data->tree_type = TREE_TOKEN;
			list_remove_head_token(&all_data->token_list);
		}
		parser_push_back(&all_data->parser.parser_stack, goto_state);
		return (0);
	}
	else
		return (-1);
}
