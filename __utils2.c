/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:29:13 by machlouj          #+#    #+#             */
/*   Updated: 2022/12/30 15:12:24 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*ft_construct_enode(void)
{
	t_exec_node	*enode;

	enode = ft_xalloc(sizeof(t_exec_node));
	enode->type = ENODE;
	enode->cmd = NULL;
	ft_collect_tmp_mem(enode);
	return ((t_tree *) enode);
}

t_tree	*ft_construct_pnode(t_tree *left, t_tree *right)
{
	t_pipe_node	*pnode;

	pnode = ft_xalloc(sizeof(t_pipe_node));
	ft_collect_tmp_mem(pnode);
	pnode->type = PNODE;
	pnode->left = left;
	pnode->right = right;
	return ((t_tree *) pnode);
}

void	join_args(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_cmd	*create_arg(char *value)
{
	t_cmd	*ans;

	ans = ft_xalloc(sizeof(t_cmd));
	ft_add_to_tmp_memory(&g_minishell.tmp_memory, ft_create_memory_node(ans));
	if (!ans)
		exit(1);
	ans->val = ft_strdup(value);
	ft_add_to_tmp_memory(&g_minishell.tmp_memory, ft_create_memory_node(ans->val));
	ans->next = NULL;
	return (ans);
}

t_tree	*ft_parse_exec(t_parser *parser)
{
	t_tree		*tmp;
	int			i;

	parser->tree = ft_construct_enode();
	tmp = parser->tree;
	i = 0;
	parser->tree = ft_parse_redir(parser);
	while (parser->current && parser->current->type == WORD_T)
	{
		join_args(&((t_exec_node *)parser->tree)->cmd, create_arg(parser->current->value));
		parser->current = parser->current->next;
	}
	parser->tree = ft_parse_redir(parser);
	return (parser->tree);
}

t_tree	*ft_construct_herdoc(t_parser	*parser)
{
	t_redir_node	*ret;

	ret = ft_xalloc(sizeof(t_redir_node));
	ft_collect_tmp_mem(ret);
	ret->type = RNODE;
	ret->redir_type = parser->current->type;
	if (g_minishell.error_flag)
		return (0x0);
	ret->fd = herdoc(parser);
	ret->file = parser->current->next->value;
	ret->sub = parser->tree;
	return ((t_tree *) ret);
}

t_tree	*ft_parse_redir(t_parser *parser)
{
	while (parser->current && (parser->current->type == SREDIR_IN_T
			|| parser->current->type == SREDIR_OUT_T
			|| parser->current->type == DREDIR_OUT_T
			|| parser->current->type == HERDOC_T))
	{
		if (parser->current->type == SREDIR_IN_T)
			parser->tree = ft_construct_rnode(parser, O_RDONLY, STDIN_FILENO);
		else if (parser->current->type == SREDIR_OUT_T)
			parser->tree = ft_construct_rnode(parser,
					O_CREAT | O_TRUNC | O_WRONLY, STDOUT_FILENO);
		else if (parser->current->type == DREDIR_OUT_T)
			parser->tree = ft_construct_rnode(parser,
					O_CREAT | O_APPEND | O_WRONLY, STDOUT_FILENO);
		else if (parser->current->type == HERDOC_T)
			parser->tree = ft_construct_herdoc(parser);
		parser->current = parser->current->next->next;
	}
	return (parser->tree);
}
