#include "../includes/minishell.h"

static char	*ft_char_to_str(char c)
{
	char	*str;

	str = ft_malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

static char	get_char_to_append(char curr_char, t_expansion_flag flag, \
		t_quot_state quote_flag)
{
	char	char_to_append;

	if (quote_flag == QUOT_NON && curr_char == '*')
	{
		char_to_append = '\001';
	}
	else if (!(flag & EXP_QUOT) || \
			quote_flag == check_quote(curr_char, quote_flag))
	{
		char_to_append = curr_char;
	}
	else
	{
		char_to_append = '\0';
	}
	return (char_to_append);
}

void	no_variable_expansion(char *word, t_expansion_flag flag, \
		t_expansion_info *info)
{
	char		char_to_append;
	char		*str;
	char		*temp;

	char_to_append = get_char_to_append(*word, flag, info->quote_flag);
	str = ft_malloc(2);
	str[0] = char_to_append;
	str[1] = '\0';
	temp = info->curr_word;
	info->curr_word = ft_strjoin(info->curr_word, str);
	free(str);
	free(temp);
	update_last_node_word(info->new_list, info->curr_word);
}
