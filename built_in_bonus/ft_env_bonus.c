/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:20:30 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:19:17 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

int	ft_env(t_cmd *cmd)
{
	print_envp(*cmd->envp_list);
	return (EXECUTION_SUCCESS);
}
