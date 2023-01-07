/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __utils1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:37:38 by machlouj          #+#    #+#             */
/*   Updated: 2023/01/07 20:24:43 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_drop_tmp_memory(void)
{
	t_memory	*next;

	while (g_minishell.tmp_memory)
	{
		next = g_minishell.tmp_memory->next;
		free(g_minishell.tmp_memory->ptr);
		free(g_minishell.tmp_memory);
		g_minishell.tmp_memory = next;
	}
	g_minishell.tmp_memory = 0x0;
}

void	ft_drop_memory(void)
{
	t_memory	*next;

	while (g_minishell.tmp_memory)
	{
		next = g_minishell.tmp_memory->next;
		free(g_minishell.tmp_memory->ptr);
		free(g_minishell.tmp_memory);
		g_minishell.tmp_memory = next;
	}
	while (g_minishell.perm_memory)
	{
		next = g_minishell.perm_memory->next;
		free(g_minishell.perm_memory->ptr);
		free(g_minishell.perm_memory);
		g_minishell.perm_memory = next;
	}
	g_minishell.perm_memory = 0x0;
}

t_tree	*ft_construct_rnode(t_parser *parser, int flag, int fd)
{
	t_redir_node	*ret;

	ret = ft_collect_tmp_mem(ft_xalloc(sizeof(t_redir_node)));
	ret->type = RNODE;
	ret->redir_type = parser->current->type;
	ret->fd = fd;
	ret->file = parser->current->next->value;
	ret->flag = flag;
	ret->sub = parser->tree;
	return ((t_tree *) ret);
}

int	ft_update_readline(void)
{
	return (0);
}

void	ft_handle_herdoc_sigint(int sig)
{
	(void)sig;
	rl_done = 1;
	g_minishell.error_flag = 1;
	return ;
}
