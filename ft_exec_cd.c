/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 23:30:02 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/02 21:08:52 by mzridi           ###   ########.fr       */
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
			printf("bigshell: cd: %s: No such file or directory\n", oldpwd);
		else
		{
			if (ft_key_exist(shell->env_head, "OLDPWD"))
				ft_add_env(&shell->env_head, "OLDPWD", tmp_oldpwd);
			ft_pwd();
		}
	}
	else
		printf("bigshell: cd: OLDPWD not set\n");
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
			printf("bigshell: cd: %s: No such file or directory\n", home);
		else if (ft_key_exist(shell->env_head, "OLDPWD"))
			ft_add_env(&shell->env_head, "OLDPWD", oldpwd);
	}
	else
		printf("bigshell: cd: HOME not set\n");
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
