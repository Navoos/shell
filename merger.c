/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:11:16 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/10/09 22:09:18 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_merge_quoted_words(t_tokens **head, t_env_list *env_list)
{
	t_tokens	*tmp;
	t_tokens	*next;
	char		*str;

	tmp = *head;
	while (tmp)
	{
		str = tmp->value;
		if (tmp->type != SQWORD_T)
			ft_get_word(tmp, env_list, &str);
		if (tmp->type == WORD_T || tmp->type == SQWORD_T
			|| tmp->type == DQWORD_T)
		{
			if (tmp->type == WORD_T)
				next = ft_merge_words(tmp, &str, env_list);
			else if (tmp->type == SQWORD_T)
				next = ft_merge_swords(tmp, &str, env_list);
			else
				next = ft_merge_dwords(tmp, &str, env_list);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
}

t_tokens	*ft_merge_words(t_tokens *tmp, char **str, t_env_list *env_list)
{
	t_tokens	*current;
	int			merged;

	merged = 0;
	current = __norm_ft_merge_init(tmp);
	while (current && (current->type == SQWORD_T || current->type == DQWORD_T))
	{
		if (current->type == DQWORD_T)
			*str = ft_collect_tmp_mem(ft_strjoin(*str,
						ft_expand(current->value, env_list)));
		else
			*str = ft_collect_tmp_mem(ft_strjoin(*str, current->value));
		current = current->next;
		merged = 1;
	}
	if (tmp)
		ft_is_merged(&tmp, merged, str, current);
	if (current)
		current->prev = tmp;
	return (current);
}

t_tokens	*ft_merge_swords(t_tokens *tmp, char **str, t_env_list *env_list)
{
	t_tokens	*current;

	current = __norm_ft_merge_init(tmp);
	while (current && (current->type == SQWORD_T
			|| current->type == WORD_T || current->type == DQWORD_T))
	{
		if (current->type == DQWORD_T || current->type == WORD_T)
			*str = ft_strjoin(*str, ft_expand(current->value, env_list));
		else
			*str = ft_strjoin(*str, current->value);
		ft_collect_tmp_mem(*str);
		current = current->next;
	}
	if (tmp)
	{
		tmp->value = *str;
		if (tmp->type != WORD_T)
			tmp->herdoc_expandble = 0;
		tmp->type = WORD_T;
		tmp->next = current;
	}
	if (current)
		current->prev = tmp;
	return (current);
}

t_tokens	*ft_merge_dwords(t_tokens *tmp, char **str, t_env_list *env_list)
{
	t_tokens	*current;

	current = __norm_ft_merge_init(tmp);
	while (current && (current->type == WORD_T
			|| current->type == DQWORD_T || current->type == SQWORD_T))
	{
		if (current->type == DQWORD_T || current->type == WORD_T)
			*str = ft_strjoin(*str, ft_expand(current->value, env_list));
		else
			*str = ft_strjoin(*str, current->value);
		ft_collect_tmp_mem(*str);
		current = current->next;
	}
	if (tmp)
		inside_merge(tmp, str, current);
	if (current)
		current->prev = tmp;
	return (current);
}
