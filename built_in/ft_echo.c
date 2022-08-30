#include "../includes/minishell.h"
#include <stdio.h>

static int	check_opt(t_list *list)
{
	t_word_data	*word_data;

	word_data = list->head->data;
	if (!ft_strncmp(word_data->word, "-n", 3))
		return (0);
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int			display_return;
	t_list		*word_list;
	t_node		*current;
	t_word_data	*word_data;

	word_list = cmd->content.simple.words;
	display_return = check_opt(word_list);
	current = word_list->head;
	if (!display_return)
		current = current->next;
	while (current)
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
