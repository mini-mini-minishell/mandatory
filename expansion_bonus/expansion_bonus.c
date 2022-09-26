/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:34 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:21:09 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

t_list	*expansion_all(t_list *words, t_list *env)
{
	return (expand_word_list(words, env, EXP_ALL));
}

t_list	*expansion_heredoc_content(t_list *words, t_list *env)
{
	return (expand_word_list(words, env, EXP_VARIABLE));
}
