/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:48:45 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/10 13:01:15 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_split_to_mem(char **split)
{
	int	i;

	i = 0;
	if (split)
		ft_add_to_tmp_memory(&g_minishell.tmp_memory,
			ft_create_memory_node(split));
	while (split && split[i])
	{
		ft_add_to_tmp_memory(&g_minishell.tmp_memory,
			ft_create_memory_node(split[i]));
		i++;
	}
}

int	ft_add_command_to_mem(char *cmd)
{
	if (cmd)
	{
		ft_add_to_tmp_memory(&g_minishell.tmp_memory,
			ft_create_memory_node(cmd));
		return (0);
	}
	else
		return (-1);
}

void	ft_init_env(t_env **env_head, char **envp)
{
	int		i;
	char	**split;
	char	*val;

	i = 0;
	g_minishell.oldpwd = 1;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		ft_add_split_to_mem(split);
		if (split && split[1])
			val = split[1];
		else
		{
			val = ft_xalloc(sizeof(char));
			ft_add_to_tmp_memory(&g_minishell.tmp_memory,
				ft_create_memory_node(val));
			val[0] = '\0';
		}
		ft_add_env(env_head, split[0], val);
		i++;
	}
}

void	ft_increment_shlvl(t_shell *shell)
{
	char	*shlvl;
	int		shlvl_int;
	char	*shlvl_str;

	shlvl = ft_get_env(shell->env_head, "SHLVL");
	if (!shlvl)
	{
		ft_add_env(&shell->env_head, "SHLVL", "1");
		return ;
	}
	shlvl_int = ft_atoi(shlvl);
	shlvl_int++;
	shlvl_str = ft_itoa(shlvl_int);
	ft_add_env(&shell->env_head, "SHLVL", shlvl_str);
	if (shlvl_str)
		free(shlvl_str);
}

void	ft_init_shell(t_shell *shell, t_env *env_head, char **envp)
{
	char	*pwd;

	ft_init_env(&env_head, envp);
	pwd = ft_get_env(env_head, "PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		ft_add_env(&env_head, "PWD", pwd);
		ft_add_to_tmp_memory(&g_minishell.tmp_memory,
			ft_create_memory_node(pwd));
	}
	shell->env_head = env_head;
	shell->cwd = getcwd(NULL, 0);
	ft_increment_shlvl(shell);
}
