/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 23:21:37 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/06 20:21:52 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(0x0, 0);
	if (!pwd)
	{
		if (shell->cwd)
		{
			ft_putstr_fd(shell->cwd, 1);
			ft_putchar_fd('\n', 1);
		}
		else
		{
			ft_putstr_fd("bigshell: pwd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory\n", 2);
		}
		return ;
	}
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
}
