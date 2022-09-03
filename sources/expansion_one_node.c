#include "../includes/minishell.h"

static t_trim_flag	update_trim_flag(t_trim_flag flag)
{
	if (flag & TRIM_BACK)
		return (TRIM_PREV_NODE);
	return (TRIM_NON);
}

static t_list	*remove_null_node(t_list *lst)
{
	t_list	*head;
	t_list	*curr;
	t_list	*temp;

	head = NULL;
	while (lst)
	{
		if (lst->word == NULL)
		{
			temp = lst;
			lst = lst->next;
			free_word_one_node(temp);
			continue ;
		}
		if (head == NULL)
			head = lst;
		else
			curr->next = lst;
		curr = lst;
		lst = lst->next;
	}
	return (head);
}


void	init_info(t_expansion_info *info)
{
	// t_buffer		curr_word; //주서끄
	info->curr_word = NULL;
	info->new_list = ft_malloc(sizeof(t_list));
	info->quote_flag = 0;
}

//variable_expansion, word splitting in here.
//expand current node (possibly seperate into serveral node),
//add it to of new_list's lastnode. 
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
			expand_variable(&word, env, flag, &info); // 여기까지 토욜 끝
		else
			no_variable_expansion(word++, flag, &info);
	}
	if (info.new_list == NULL)
	{
		addback_word_list(new_word_list(info.curr_word.word), &(info.new_list));
	}
	if (flag & EXP_ASTERISK)
	{
		filename_expansion(&(info.new_list));
	}
	info.new_list = remove_null_node(info.new_list);
	return (info.new_list);
}
