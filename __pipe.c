/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:16:47 by machlouj          #+#    #+#             */
/*   Updated: 2022/12/30 11:50:28 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	__pipe__(t_tree *tree, t_env_list **env_list)
// {
// 	int	__fd[2];
// 	int	__pid;

// 	if (pipe(__fd) == -1)
// 		exit (1);
// 	__pid = fork();
// 	if (__pid < 0)
// 	{
// 		perror("ERROR");
// 		return ;
// 	}
// 	if (__pid == 0)
// 		__left__(__fd, tree, env_list);
// 	__pid = fork();
// 	if (__pid == -1)
// 		exit(1);
// 	if (!__pid)
// 		__right__(__fd, tree, env_list);
// 	close(__fd[0]);
// 	close(__fd[1]);
// 	wait(NULL);
// 	wait(NULL);
// }

// void	__right__(int __fd[2], t_tree *tree, t_env_list **env_list)
// {
// 	dup2(__fd[0], STDIN_FILENO);
// 	close(__fd[1]);
// 	ft_print_tree(((t_pipe_node *)tree)->right, env_list);
// 	exit(0);
// }

// void	__left__(int __fd[2], t_tree *tree, t_env_list **env_list)
// {
// 	dup2(__fd[1], STDOUT_FILENO);
// 	close(__fd[0]);
// 	ft_print_tree(((t_pipe_node *)tree)->left, env_list);
// 	exit(0);
// }
