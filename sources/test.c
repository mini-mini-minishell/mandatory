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
	// exit(0); // ---------
}

// void	print_word_data(t_list *word_list)
// {
// 	t_list			word_list;
// 	t_node			*current_node;
// 	t_word_data		*word_data;
// 	size_t			index;

// 	current_node = word_list->tail;
// 	index = 0;
// 	while (index < word_list->count)
// 	{
// 		word_data = current_node->data;
// 		printf("%d[%s]\n", word_data->word, index);
// 		current_node = current_node->prev;
// 		++index;
// 	}
// 	// exit(0); // ---------
// }


void	print_tree_stack(t_list tree_stack)
{
	t_tree_data	*tree_data;
	t_node		*temp;
	t_word_data	*word_data;

	tree_data = tree_stack.head->data;
	if (tree_data->content.cmd->type == CMD_SIMPLE)
	{
		temp = tree_data->content.cmd->content.simple.words->head;
		while (temp)
		{
			word_data = temp->data;
			temp = temp->next;
		}
	}
	else if (tree_data->content.cmd->type == CMD_CONNECT)
	{
		//printf("-----CONNECT----\n");
		// temp = tree_data->content.cmd->content.connect.left->content.simple.words->count;
		// while (temp)
		// {
		// 	word_data = temp->data;
		// 	//printf("connect left : ");
		// 	// //printf("%s ",); 
		// 	temp = temp->next;
		// }
		//printf("Connect Finish\n");
	}
	else if (tree_data->content.cmd->type == CMD_SUBSHELL)
	{
		//printf("----SUBSHELL----\n");
		//printf("Subshell Finish\n");
	}
	// exit(0);
}
