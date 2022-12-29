/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machlouj <machlouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:13:13 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/10/04 22:29:40 by machlouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void	ft_apply_redir(t_redir_node *redir, int *flag)
{
	int	fd;

	if (redir->type == ENODE)
		return ;
	ft_apply_redir(((t_redir_node *)((t_redir_node *)redir)->sub), flag);
	if (!*flag)
		return ;
	if (redir->redir_type == HERDOC_T)
	{
		dup2(redir->fd, STDIN_FILENO);
		close(redir->fd);
	}
	else
	{
		fd = open(redir->file, redir->flag, 0644);
		if (fd < 0)
			return (*flag = 0, perror(redir->file));
		if (redir->redir_type == SREDIR_IN_T)
			dup2(fd, redir->fd);
		else if (redir->redir_type == DREDIR_OUT_T
			|| redir->redir_type == SREDIR_OUT_T)
			dup2(fd, redir->fd);
	}
}

void	__redir__(t_redir_node *r, t_env_list **env)
{
	t_exec_node	*cmd;	
	int			flag;

	flag = 1;
	ft_apply_redir(r, &flag);
	cmd = 0x0;
	if (flag)
	{
		while (r->type != ENODE)
			r = (t_redir_node *) r->sub;
		ft_print_tree((t_tree *)r, env);
	}
}
