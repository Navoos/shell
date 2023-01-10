/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __utils3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 22:08:18 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/09 22:09:11 by mzridi           ###   ########.fr       */
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
