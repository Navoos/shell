/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 23:30:02 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/06 20:27:41 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_pwd(t_shell *shell ,char *val)
{
	if (val)
	{
		if (shell->cwd)
			free(shell->cwd);
		shell->cwd = ft_strdup(val);
		ft_add_env(&shell->env_head, "PWD", val);
	}
}

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
			ft_add_pwd(shell, getcwd(NULL, 0));
			ft_pwd(shell);
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
		{
			ft_add_env(&shell->env_head, "OLDPWD", oldpwd);
			ft_add_pwd(shell, getcwd(NULL, 0));
		}
		else
			ft_add_pwd(shell, getcwd(NULL, 0));
	}
	else
		ft_putstr_fd("bigshell: cd: HOME not set\n", 2);
}

void	ft_go_point(t_shell *shell)
{
	char	*oldpwd;
	char	*tmp;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		printf("bigshell: cd: error retrieving current directory:\
 getcwd: cannot access parent directories: No such file or directory\n");
		oldpwd = shell->cwd;
		tmp = shell->cwd;
		if (oldpwd)
			shell->cwd = ft_strjoin(oldpwd, "/.");
		if (tmp)
			free(tmp);
	}
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
		{
			ft_add_env(&shell->env_head, "OLDPWD", oldpwd);
			ft_add_pwd(shell, getcwd(NULL, 0));
		}
		else
			ft_add_pwd(shell, getcwd(NULL, 0));
	}
}
