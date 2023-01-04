/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 23:30:02 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/04 21:45:05 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_go_back(t_shell *shell)
{
	char	*oldpwd;
	char	*tmp_oldpwd;

	tmp_oldpwd = getcwd(NULL, 0);
	oldpwd = ft_get_env(shell->env_head, "OLDPWD");
	if (oldpwd)
	{
		if (chdir(oldpwd) == -1)
		{
			ft_putstr_fd("bigshell: cd: ", 2);
			ft_putstr_fd(oldpwd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
		{
			if (ft_key_exist(shell->env_head, "OLDPWD"))
				ft_add_env(&shell->env_head, "OLDPWD", tmp_oldpwd);
			ft_pwd();
		}
	}
	else
		ft_putstr_fd("bigshell: cd: OLDPWD not set\n", 2);
	if (tmp_oldpwd)
		free(tmp_oldpwd);
}

void	ft_go_home(t_shell *shell)
{
	char	*home;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	home = ft_get_env(shell->env_head, "HOME");
	if (home)
	{
		if (chdir(home) == -1)
		{
			ft_putstr_fd("bigshell: cd: ", 2);
			ft_putstr_fd(home, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else if (ft_key_exist(shell->env_head, "OLDPWD"))
			ft_add_env(&shell->env_head, "OLDPWD", oldpwd);
	}
	else
		ft_putstr_fd("bigshell: cd: HOME not set\n", 2);
}

void	ft_go_point(t_shell *shell)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		printf("bigshell: cd: error retrieving current directory:\
 getcwd: cannot access parent directories: No such file or directory\n");
	else if (ft_key_exist(shell->env_head, "OLDPWD"))
		ft_add_env(&shell->env_head, "OLDPWD", oldpwd);
}

void	ft_cd(t_shell *shell, char **args)
{
	char	*oldpwd;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		ft_go_home(shell);
	else if (ft_strcmp(args[1], "-") == 0)
		ft_go_back(shell);
	else if (ft_strcmp(args[1], ".") == 0)
		ft_go_point(shell);
	else
	{
		oldpwd = getcwd(NULL, 0);
		if (chdir(args[1]) == -1)
			printf("bigshell: cd: %s: No such file or directory\n", args[1]);
		else if (ft_key_exist(shell->env_head, "OLDPWD"))
			ft_add_env(&shell->env_head, "OLDPWD", oldpwd);
	}
}
