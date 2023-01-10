/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:33:28 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/10 11:36:34 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup_pipe(int *fd, int target_fd, t_pipe_node *pnode, t_shell *shell)
{
	if (target_fd == STDIN_FILENO)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		ft_exec_main(pnode->right, shell);
		exit(g_minishell.exit_status);
	}
	else
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		ft_exec_main(pnode->left, shell);
		exit(g_minishell.exit_status);
	}
}

void	ft_exec_pipe(t_pipe_node *pnode, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		return (perror("ERROR"));
	if (pid == 0)
		ft_dup_pipe(fd, STDOUT_FILENO, pnode, shell);
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror("ERROR"));
		if (pid == 0)
			ft_dup_pipe(fd, STDIN_FILENO, pnode, shell);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	g_minishell.exit_status = WEXITSTATUS(status);
	wait(NULL);
}
