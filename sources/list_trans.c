#include "../includes/minishell.h"

char	**trans_word_list_2_array(t_list word_list)
{
	t_word_data	*data;
	t_node		*current;
	char		**word_array;
	int			i;

	current = word_list.head;
	word_array = ft_malloc(sizeof(char *) * (word_list.count + 1));
	i = 0;
	while(current)
	{
		data = current->data;
		word_array[i] = ft_malloc(sizeof(char) * (ft_strlen(data->word) + 1));
		ft_strlcpy(word_array[i], data->word, ft_strlen(data->word) + 1);
		current = current->next;
		++i;
	}
	return (word_array);
}


// struct s_env_data
// {
// 	char	*key;
// 	char	*value;
// };

char	**trans_envp_list_2_array(t_list envp_list)
{
	t_env_data	*data;
	t_node		*current;
	char		**envp_array;
	int			i;
	
	envp_array = ft_malloc(sizeof(char *) * (envp_list.count + 1));
	i = 0;
	while (current)
	{
		data = current->data;
		current = envp_list.head;
		envp_array[i] = data->value;
		++i;
	}
}