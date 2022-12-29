/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:03:24 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/10/03 12:39:57 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_add_out_redir(char *s, t_tokens **token)
{
	if (*(s + 1) == '>')
	{
		ft_push_back_token(token,
			ft_create_token(DREDIR_OUT_T, ft_strdup(">>")));
		return (2);
	}
	ft_push_back_token(token, ft_create_token(SREDIR_OUT_T, ft_strdup(">")));
	return (1);
}

unsigned int	ft_add_in_redir(char *s, t_tokens **token)
{
	if (*(s + 1) == '<')
	{
		ft_push_back_token(token, ft_create_token(HERDOC_T, ft_strdup("<<")));
		return (2);
	}
	ft_push_back_token(token, ft_create_token(SREDIR_IN_T, ft_strdup("<")));
	return (1);
}

unsigned int	ft_add_pipe(char *s, t_tokens **token)
{
	ft_push_back_token(token, ft_create_token(PIPE_T, ft_strndup(s, 1)));
	return (1);
}

unsigned int	ft_add_word(char *s, t_tokens **token)
{
	int	i;
	int	type;

	i = 0;
	type = WORD_T;
	if (*s == 0)
		return (0);
	while (!ft_strchr(" \'\"><|", s[i]) && s[i])
		i += 1;
	if ((*token) && ((*token)->type == SQWORD_T
			|| ((*token)->next && (*token)->next->type == SQWORD_T)))
		type = SQWORD_T;
	else if ((*token) && ((*token)->type == DQWORD_T
			|| ((*token)->next && (*token)->next->type == DQWORD_T)))
		type = DQWORD_T;
	ft_push_back_token(token, ft_create_token(type, ft_strndup(s, i)));
	return (i);
}

unsigned int	ft_add_space(char *s, t_tokens **token)
{
	int	i;

	i = 0;
	while ((s[i] == ' ' || s[i] == '\t') && s[i])
		i += 1;
	ft_push_back_token(token, ft_create_token(SPACE_T, ft_strdup(" ")));
	return (i);
}
