/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:47:55 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/08 19:17:59 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_redir(t_redir_node *redir_node, t_shell *shell)
{
	int		fd;

	if (redir_node && redir_node->type == ENODE)
		return ;
	ft_exec_redir((t_redir_node *)redir_node->sub, shell);
	if (redir_node->redir_type == HERDOC_T)
	{
		dup2(redir_node->fd, 0);
		close(redir_node->fd);
	}	
	else
	{
		fd = open(redir_node->file, redir_node->flag, 0644);
		if (fd < 0)
			return (perror(redir_node->file));
		else if (redir_node->redir_type == SREDIR_OUT_T
			|| redir_node->redir_type == SREDIR_IN_T
			|| redir_node->redir_type == DREDIR_OUT_T)
			dup2(fd, redir_node->fd);
	}
}

void	ft_redir(t_redir_node *redir_node, t_shell *shell)
{
	t_redir_node	*tmp;

	ft_exec_redir(redir_node, shell);
	tmp = redir_node;
	while (tmp && tmp->type != ENODE)
		tmp = (t_redir_node *)tmp->sub;
	if (tmp->type == ENODE)
		ft_exec_main((t_tree *)tmp, shell);
}
