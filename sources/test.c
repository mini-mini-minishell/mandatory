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

void	print_tree_stack(t_list tree_stack)
{
	t_tree_data	*tree_data;
	t_node		*temp;
	t_word_data	*word_data;

	tree_data = tree_stack.head->data;
	// printf("000000!!!!!!\n");
	// printf("cmd %p \n", tree_data->content.cmd);
	// printf("type %d \n", tree_data->content.cmd->type);
	if (tree_data->content.cmd->type == CMD_SIMPLE)
	{
		temp = tree_data->content.cmd->content.simple.words->head;
		printf("1 \n");
		while (temp)
		{
			word_data = temp->data;
			printf("word : ");
			printf("%s \n", word_data->word);
			temp = temp->next;
		}
		printf("Simple finish\n");
	}
	else if (tree_data->content.cmd->type == CMD_CONNECT)
	{
		printf("-----CONNECT----\n");
		printf("%zu is exist on the left \n", tree_data->content.cmd->content.connect.left->content.simple.words->count);
		printf("%zu is exist on the right \n", tree_data->content.cmd->content.connect.right->content.simple.words->count);
		// temp = tree_data->content.cmd->content.connect.left->content.simple.words->count;
		// while (temp)
		// {
		// 	word_data = temp->data;
		// 	printf("connect left : ");
		// 	// printf("%s ",); 
		// 	temp = temp->next;
		// }
		printf("Connect Finish\n");
	}
	else if (tree_data->content.cmd->type == CMD_SUBSHELL)
	{
		printf("----SUBSHELL----\n");
		printf("Subshell Finish\n");
	}
	exit(0);
}
