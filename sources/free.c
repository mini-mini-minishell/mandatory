#include "../includes/minishell.h"

void	free_redir(t_list *redir_list)
{
	t_node			*temp;
	t_redir_data	*temp_data;
	
	while (redir_list->count)
	{
		temp = list_pop_back(redir_list);
		temp_data = temp->data;
		free(temp_data->heredoc_eof);
		free(temp_data->file_content);
		free(temp_data);
		free(temp);
	}
	free(redir_list);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->redir_list != NULL)
		free_redir(cmd->redir_list);
	if (cmd->type == CMD_SIMPLE)
	{
		if (cmd->content.simple.words != NULL)
			word_list_remove_all(cmd->content.simple.words);
		free(cmd);
	}
	else if (cmd->type == CMD_CONNECT)
	{
		free_cmd(cmd->content.connect.left);
		free_cmd(cmd->content.connect.right);
		free(cmd);
	}
	else if (cmd->type == CMD_SUBSHELL)
	{
		free_cmd(cmd->content.subshell.cmd);
		free(cmd);
	}
	else
		return ;
}

void	free_tree_stack(t_parser *parser)
{
	t_node			*temp;
	t_tree_data		*temp_data;

	while (parser->tree_stack.count)
	{
		temp = list_pop_back(&parser->tree_stack);
		temp_data = temp->data;
		if (temp_data->tree_type == TREE_WORD)
			free(temp_data->content.word);
		else if (temp_data->tree_type == TREE_ELEMENT)
			free(temp_data->content.element);
		else if (temp_data->tree_type == TREE_CMD)
			free_cmd(temp_data->content.cmd);
		else if (temp_data->tree_type == TREE_REDIR_LIST)
			free_redir(temp_data->content.redir_list);
		free(temp_data);
		free(temp);
	}
}

void	free_parser(t_parser *parser)
{
	// t_heredoc_node	*temp;
	// t_heredoc_node	*next;

	free_tree_stack(parser);
	while (parser->parser_stack.count)
		stack_pop_back(&parser->parser_stack, parser->parser_stack.count);
	// temp = parser->heredoc_list.head;
	// while (temp)
	// {
	// 	next = temp->next;
	// 	free_redir(temp->data);
	// 	temp = next;
	// }
}