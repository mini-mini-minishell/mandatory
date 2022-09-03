#include "../includes/minishell.h"

// char	*expansion_heredoc_eof(char *orig_str)
// {
// 	t_buffer		new_buffer;
// 	t_quot_state	quote_flag;

// 	if (!orig_str)
// 	{
// 		return (NULL);
// 	}
// 	new_buffer = init_buffer(NULL);
// 	quote_flag = QUOT_NON;
// 	while (*orig_str)
// 	{
// 		if (quote_flag == check_quote(*orig_str, quote_flag))
// 			append_char_to_buffer(&new_buffer, *orig_str);
// 		orig_str++;
// 	}
// 	return (new_buffer.word);
// }

t_list	*expansion_all(t_list *words, t_list *env)
{
	return (expand_word_list(words, env, EXP_ALL));
}

// t_word_list	*expansion_heredoc_content(t_word_list *words, t_env_list *env)
// {
// 	return (expand_word_list(words, env, EXP_VARIABLE));
// }
