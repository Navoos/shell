/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 23:30:02 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/10 13:10:24 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_pwd(t_shell *shell, char *val)
{
	if (val)
	{
		if (shell->cwd)
			free(shell->cwd);
		shell->cwd = ft_strdup(val);
		ft_add_env(&shell->env_head, "PWD", val);
		free(val);
		ft_add_to_perm_memory(&g_minishell.perm_memory,
			ft_create_memory_node(shell->cwd));
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
			ft_print_error("cd", oldpwd);
			g_minishell.exit_status = 1;
		}
		else
		{
			if (g_minishell.oldpwd++ >= 1)
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
			ft_print_error("cd", home);
			g_minishell.exit_status = 1;
		}
		else if (g_minishell.oldpwd++ >= 1)
		{
			ft_add_env(&shell->env_head, "OLDPWD", oldpwd);
			ft_add_pwd(shell, getcwd(NULL, 0));
		}
		else
			ft_add_pwd(shell, getcwd(NULL, 0));
	}
	else
		ft_putstr_fd("bigshell: cd: HOME not set\n", 2);
	if (oldpwd)
		free(oldpwd);
}

void	ft_go_point(t_shell *shell)
{
	char	*oldpwd;
	char	*tmp;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_putstr_fd("bigshell: cd: error retrieving current directory:\
 getcwd: cannot access parent directories: No such file or directory\n", 2);
		oldpwd = shell->cwd;
		tmp = shell->cwd;
		if (oldpwd)
			shell->cwd = ft_strjoin(oldpwd, "/.");
		if (tmp)
			free(tmp);
	}
	else if (g_minishell.oldpwd++ >= 1)
	{
		ft_add_env(&shell->env_head, "OLDPWD", oldpwd);
		ft_add_pwd(shell, getcwd(NULL, 0));
	}
	else
		ft_add_pwd(shell, getcwd(NULL, 0));
	if (oldpwd)
		free(oldpwd);
}

void	ft_cd(t_shell *shell, char **args)
{
	char	*oldpwd;

	g_minishell.exit_status = 0;
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
			ft_print_error("cd", args[1]);
		else if (g_minishell.oldpwd++ >= 1)
		{
			ft_add_env(&shell->env_head, "OLDPWD", oldpwd);
			ft_add_pwd(shell, getcwd(NULL, 0));
		}
		else
			ft_add_pwd(shell, getcwd(NULL, 0));
		if (oldpwd)
			free(oldpwd);
	}
}
