/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:33:28 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/05 21:25:59 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_pipe(t_pipe_node *pnode, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		return (perror("ERROR"));
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		ft_exec_main(pnode->left, shell);
		exit(0);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror("ERROR"));
		if (pid == 0)
		{
			dup2(fd[0], 0);
			close(fd[1]);
			ft_exec_main(pnode->right, shell);
			exit(0);
		}
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}
