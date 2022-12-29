/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_norm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:31:52 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/09/29 11:32:26 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__norm_ft_tokenize_cmd(char *str, t_tokens **token, int *i)
{
	if (*str && *str == '$')
		*i += ft_add_dollar(str, token);
	else if (*str && *str == '>')
		*i += ft_add_out_redir(str, token);
	else if (*str && *str == '<')
		*i += ft_add_in_redir(str, token);
	else if (*str && *str == '|')
		*i += ft_add_pipe(str, token);
}

void	__norm_ft_add_dqoute(char *str, t_tokens **token, int *i)
{
	int				quote_flag;

	quote_flag = 0;
	quote_flag = ft_add_dquote(str, token);
	if (quote_flag == -1)
	{
		ft_putstr_fd("ERROR : Missing `\"", STDERR_FILENO);
		g_minishell.error_flag = 1;
		*i = -1;
		return ;
	}
	*i += quote_flag;
}

void	__norm_ft_add_sqoute(char *str, t_tokens **token, int *i)
{
	int				quote_flag;

	quote_flag = 0;
	quote_flag = ft_add_squote(str, token);
	if (quote_flag == -1)
	{
		ft_putstr_fd("ERROR : Missing `\'", STDERR_FILENO);
		g_minishell.error_flag = 1;
		*i = -1;
		return ;
	}
	*i += quote_flag;
}
