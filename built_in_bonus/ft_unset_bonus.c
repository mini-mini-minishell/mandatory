/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:20:50 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:19:35 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

int	ft_unset(t_cmd *cmd)
{
	t_node		*current;
	t_node		*target;
	t_word_data	*data;

	current = cmd->content.simple.words->head;
	while (current)
	{
		data = current->data;
		if (!data->word)
			return (EXECUTION_SUCCESS);
		else
		{
			target = envp_search_node_by_key(cmd->envp_list, data->word);
			if (!target)
				return (EXECUTION_SUCCESS);
			envp_delete_node_by_target(cmd->envp_list, &target);
		}
		current = current->next;
	}
	return (EXECUTION_SUCCESS);
}
