/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:06:21 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/09/29 11:08:14 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_syntax_redir(t_tokens *token)
{
	t_tokens	*next;

	while (token)
	{
		if (token->type == SREDIR_IN_T
			|| token->type == SREDIR_OUT_T
			|| token->type == DREDIR_OUT_T
			|| token->type == HERDOC_T)
		{
			next = ft_get_next_token(token);
			if ((next && next->type != WORD_T) || !next)
			{
				g_minishell.error_flag = 1;
				if (token->type != HERDOC_T)
					ft_putstr_fd("ERROR : Syntax error for redirection",
						STDERR_FILENO);
				else
					ft_putstr_fd("ERROR : Syntax error for herdoc",
						STDERR_FILENO);
				return ;
			}
		}
		token = token->next;
	}
}

void	ft_check_syntax_pipe(t_tokens *token)
{
	t_tokens	*prev;
	t_tokens	*next;

	while (token)
	{
		if (token->type == PIPE_T)
		{
			prev = ft_get_prev_token(token);
			next = ft_get_next_token(token);
			if (!(prev && prev->type == WORD_T && (next && (next->type == WORD_T
							|| next->type == SREDIR_IN_T
							|| next->type == DREDIR_OUT_T
							|| next->type == HERDOC_T
							|| next->type == SREDIR_OUT_T))))
			{
				g_minishell.error_flag = 1;
				ft_putstr_fd("ERROR : Syntax error for pipe", STDERR_FILENO);
				return ;
			}
		}
		token = token->next;
	}
}
