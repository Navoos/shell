/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:27:02 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/10/06 13:28:04 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inside_merge(t_tokens *tmp, char **str, t_tokens *current)
{
	tmp->value = *str;
	if (tmp->type != WORD_T)
		tmp->herdoc_expandble = 0;
	tmp->type = WORD_T;
	tmp->next = current;
}

t_tokens	*__norm_ft_merge_init(t_tokens *tmp)
{
	t_tokens	*current;

	current = 0x0;
	if (tmp)
		current = tmp->next;
	return (current);
}

void	ft_is_merged(t_tokens **tmp, int merged, char **str, t_tokens *current)
{
	(*tmp)->value = *str;
	if ((*tmp)->type != WORD_T || merged)
		(*tmp)->herdoc_expandble = 0;
	(*tmp)->type = WORD_T;
	(*tmp)->next = current;
}
