/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:12:20 by yakhoudr          #+#    #+#             */
/*   Updated: 2023/01/06 16:25:54 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_push_back_token(t_tokens **head, t_tokens *new)
{
	t_tokens	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_tokens	*ft_create_token(int type, char *value)
{
	t_tokens	*ret;

	ret = ft_xalloc(sizeof(t_tokens));
	ret->type = type;
	ret->value = value;
	ret->next = 0x0;
	ret->prev = 0x0;
	ret->herdoc_expandble = 1;
	ft_collect_tmp_mem(ret);
	ft_collect_tmp_mem(ret->value);
	return (ret);
}

void	ft_get_word(t_tokens *tmp, t_env *env_list, char **str)
{
	t_tokens	*prev;

	prev = ft_get_prev_token(tmp);
	if ((prev && prev->type != HERDOC_T) || !prev)
	{
		*str = ft_expand(tmp->value, env_list);
		ft_collect_tmp_mem(*str);
	}
}

t_tokens	*ft_get_prev_token(t_tokens *token)
{
	if (token)
	{
		token = token->prev;
		if (token && token->type == SPACE_T)
			return (token->prev);
		return (token);
	}
	return (0x0);
}

t_tokens	*ft_get_next_token(t_tokens *token)
{
	if (token)
	{
		token = token->next;
		if (token && token->type == SPACE_T)
			return (token->next);
		return (token);
	}
	return (0x0);
}
