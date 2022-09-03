#include "../includes/minishell.h"

static t_trim_flag	update_trim_flag(t_trim_flag flag)
{
	if (flag & TRIM_BACK)
		return (TRIM_PREV_NODE);
	return (TRIM_NON);
}

static t_list	*remove_null_node(t_word_list *lst)
{
	t_word_list	*head;
	t_word_list	*curr;
	t_word_list	*temp;

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

//variable_expansion, word splitting in here.
//expand current node (possibly seperate into serveral node),
//add it to of new_list's lastnode. 
t_list	*expand_one_node(char *word, t_list *env, t_expansion_flag flag)
{
	t_expansion_info	info;

	ft_memset(&info, 0, sizeof(t_expansion_info));
	while (*word != '\0')
	{
		info.quote_flag = check_quote(*word, info.quote_flag);
		info.trim_flag = update_trim_flag(info.trim_flag);
		if ((flag & EXP_VARIABLE) && info.quote_flag != QUOT_SINGLE && \
				*word == '$')
			expand_variable(&word, env, flag, &info);
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
