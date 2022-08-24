#include "../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	print_token_data(t_all_data *all_data)
{
	t_list			token_list;
	t_node			*current_node;
	t_token_data	*token_data;
	size_t			index;

	token_list = all_data->token_list;
	current_node = token_list.tail;
	index = 0;
	while (index < token_list.count)
	{
		token_data = (t_token_data *)current_node->data;
		printf("%d[%s]\n", token_data->token_type, token_data->content);
		current_node = current_node->prev;
		++index;
	}
	exit(0); // ---------
}

#include <stdio.h> //----------------------------

void	print_tree_stack(t_list tree_stack)
{
	t_tree_data	*tree_data;
	t_node		*temp;
	t_word_data	*word_data;

	tree_data = tree_stack.head->data;
	if (tree_data->content.cmd->type == CMD_SIMPLE)
	{
		printf("-----SIMPLE-----\n");
		temp = tree_data->content.cmd->content.simple.words->head;
		while (temp)
		{
			word_data = temp->data;
			printf("word : ");
			printf("%s ", word_data->word);
			temp = temp->next;
		}
		printf("\n\n");
	}
	else if (tree_data->content.cmd->type == CMD_CONNECT)
	{
		printf("-----CONNECT----\n");
		// temp = tree_data->content.cmd->content.connect.;
		// while (temp)
		// {
		// 	word_data = temp->data;
		// 	printf("connect : ");
		// 	printf("%s ",);
		// 	temp = temp->next;
		// }
		// printf("\n\n");
	}
	else if (tree_data->content.cmd->type == CMD_SUBSHELL)
	{
		printf("----SUBSHELL----\n");
	}
	exit(0);
}
