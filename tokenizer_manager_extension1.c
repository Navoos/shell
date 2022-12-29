/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_manager_extension1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:04:24 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/09/28 11:21:53 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_add_dquote(char *s, t_tokens **token)
{
	int	i;

	i = 1;
	if (!s[i])
		return (-1);
	while (s[i] != '\"' && s[i])
	{
		i += 1;
	}
	if (s[i] == '\"')
	{
		ft_push_back_token(token,
			ft_create_token(DQWORD_T, ft_strndup(s + 1, i - 1)));
		return (i + 1);
	}
	return (-1);
}

unsigned int	ft_add_squote(char *s, t_tokens **token)
{
	int	i;

	i = 1;
	if (!s[i])
		return (-1);
	while (s[i] != '\'' && s[i])
	{
		i += 1;
	}
	if (s[i] == '\'')
	{
		ft_push_back_token(token,
			ft_create_token(SQWORD_T, ft_strndup(s + 1, i - 1)));
		return (i + 1);
	}
	return (-1);
}

unsigned int	ft_add_dollar(char *s, t_tokens **token)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\"' && s[i] != '\'')
		i += 1;
	ft_push_back_token(token, ft_create_token(WORD_T, ft_strndup(s, i)));
	return (i);
}
