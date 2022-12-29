/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:55:34 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/10/09 14:25:26 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_node(t_tokens **head, t_tokens *node)
{
	if (*head == node)
		*head = (*head)->next;
	if (node->next)
		node->next->prev = node->prev;
	if (node->prev)
		node->prev->next = node->next;
}

void	ft_skip_spaces(t_tokens **head)
{
	t_tokens	*tmp;
	t_tokens	*next;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == SPACE_T)
		{
			next = tmp->next;
			ft_skip_node(head, tmp);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
}

int	ft_find_char(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i += 1;
	}
	return (0);
}

void	ft_filter_tokens(t_tokens **token, t_env_list *env_list)
{
	ft_merge_quoted_words(token, env_list);
	ft_check_syntax_pipe(*token);
	if (g_minishell.error_flag)
		return ;
	ft_check_syntax_redir(*token);
	if (g_minishell.error_flag)
		return ;
	ft_skip_spaces(token);
}

void	ft_tokenize_cmd(t_tokens **token, char *str, t_env_list	*env_list)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == ' ')
			i += ft_add_space(&str[i], token);
		if (str[i] && str[i] == '\"')
		{
			__norm_ft_add_dqoute(&str[i], token, &i);
			if (i == -1)
				return ;
		}
		if (str[i] && str[i] == '\'')
		{
			__norm_ft_add_sqoute(&str[i], token, &i);
			if (i == -1)
				return ;
		}
		if (ft_find_char(str[i], "$><|"))
			__norm_ft_tokenize_cmd(&str[i], token, &i);
		if (str[i] && (!ft_strchr(" \'\"$><|", str[i])))
			i += ft_add_word(&str[i], token);
	}
	ft_filter_tokens(token, env_list);
}
