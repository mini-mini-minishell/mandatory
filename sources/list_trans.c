#include "../includes/minishell.h"
#include "../includes/get_next_line.h"

char	**trans_word_list_2_array(t_list word_list)
{
	t_word_data	*data;
	t_node		*current;
	char		**word_array;
	int			i;

	current = word_list.head;
	word_array = ft_malloc(sizeof(char *) * (word_list.count + 1));
	word_array[word_list.count] = NULL;
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

char	**trans_envp_list_2_array(t_list envp_list)
{
	t_env_data	*data;
	t_node		*current;
	char		**envp_array;
	int			i;
	
	envp_array = ft_malloc(sizeof(char *) * (envp_list.count + 1));
	envp_array[envp_list.count] = NULL;
	i = 0;
	current = envp_list.head;
	while (current)
	{
		data = current->data;
		envp_array[i] = ft_strjoin(data->key, "=");
		envp_array[i] = ft_strjoin_gnl(envp_array[i], data->value);
		current = current->next;
		++i;
	}
	return (envp_array);
}
