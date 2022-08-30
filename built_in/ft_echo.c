#include "../includes/minishell.h"
#include <stdio.h>

static void	*check_opt(t_list *list, int *display_return)
{
	t_word_data	*word_data;
	t_node		*current;

	current = list->head;
	word_data = current->data;
	if (!ft_strncmp(word_data->word, "-n", 3))
		*display_return = 0;
}

int	ft_echo(t_cmd *cmd)
{
	int			display_return;
	t_list		*word_list;
	t_node		*current;
	t_word_data	*word_data;
	

	display_return = 1;
	word_list = cmd->content.simple.words;
	check_opt(word_list, &display_return);
	current = word_list->head;
	if (!display_return)
		current = current->next;
	while (word_list)
	{
		word_data = current->data;
		if (word_data)
		{
			printf("%s", word_data->word);
		}
		if (word_data->word && current->next)
		{
			printf(" ");
		}
		current = current->next;
	}
	if (display_return)
	{
		printf("\n");
	}
	return (EXECUTION_SUCCESS);
}
