#include "../includes/minishell.h"

static void	remove_null_node(t_list *list)
{
	t_node		*current;
	t_node		*temp;
	t_word_data	*word_data;

	current = list->head;
	while (current)
	{
		word_data = current->data;
		// if (*word_data->word == '\0')
		if (word_data->word == NULL)
		{
			temp = current;
			current = current->next;
			word_data = temp->data;
			// free(word_data->word);
			free(word_data->variables); // free word list
			free(word_data);
			free(temp);
			continue ;
		}
		current = current->next;
	}
}

static void	init_info(t_expansion_info *info)
{
	// t_buffer		curr_word; //주서끄
	info->curr_word = NULL;
	info->new_list = ft_malloc(sizeof(t_list));
	list_init(info->new_list);
	info->quote_flag = 0;
}

#include <stdio.h>
t_list	*expand_one_node(t_node *word_node, t_list *env, t_expansion_flag flag)
{
	t_expansion_info	info;
	t_word_data			*data;
	char				*word;

	init_info(&info);
	data = word_node->data;
	word = data->word;
	while (*word != '\0')
	{
		info.quote_flag = check_quote(*word, info.quote_flag);
		// info.trim_flag = update_trim_flag(info.trim_flag); //워드스플릿 안함
		if ((flag & EXP_VARIABLE) && info.quote_flag != QUOT_SINGLE && \
				*word == '$')
			expand_variable(&word, env, flag, &info);
		else
			no_variable_expansion(word++, flag, &info);
	}
	if (!info.new_list->count)
	{
		// printf("들어옴\n");
		list_push_back(info.new_list, list_new_node(create_word_data(info.curr_word)));
	}
	//printf("count : %d\n", info.new_list->count);
	//printf("head : %p\n", info.new_list->head);
	if (flag & EXP_ASTERISK)
	{
	//	printf("%d %d\n ", flag, flag & EXP_ASTERISK);
		filename_expansion(&info.new_list);
	}
	//printf("before nn count : %d\n", info.new_list->count);
	// remove_null_node(info.new_list);
	//printf("remove after head : %p\n", info.new_list->head);
	return (info.new_list);
}

// /* chan */
// t_word_list	*expand_one_node(char *word, t_env_list *env, t_expansion_flag flag)
// {
// 	t_expansion_info	info;

// 	ft_memset(&info, 0, sizeof(t_expansion_info));
// 	while (*word != '\0')
// 	{
// 		info.quote_flag = check_quote(*word, info.quote_flag);
// 		info.trim_flag = update_trim_flag(info.trim_flag);
// 		if ((flag & EXP_VARIABLE) && info.quote_flag != QUOT_SINGLE && \
// 				*word == '$')
// 			expand_variable(&word, env, flag, &info);
// 		else
// 			no_variable_expansion(word++, flag, &info);
// 	}
// 	if (info.new_list == NULL)
// 	{
// 		addback_word_list(new_word_list(info.curr_word.word), &(info.new_list));
// 	}
// 	if (flag & EXP_ASTERISK)
// 	{
// 		filename_expansion(&(info.new_list));
// 	}
// 	info.new_list = remove_null_node(info.new_list);
// 	return (info.new_list);
// }