/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:48:45 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/06 18:13:19 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_env(t_env **env_head, char **envp)
{
	int		i;
	char	**split;
	char	*val;

	i = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (split[1])
			val = split[1];
		else
		{
			val = malloc(sizeof(char));
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

	shlvl = ft_get_env(shell->env_head, "SHLVL");
	if (!shlvl)
	{
		ft_add_env(&shell->env_head, "SHLVL", "1");
		return ;
	}
	shlvl_int = ft_atoi(shlvl);
	shlvl_int++;
	ft_add_env(&shell->env_head, "SHLVL", ft_itoa(shlvl_int));
}

void	ft_init_shell(t_shell *shell, t_env *env_head, char **envp)
{
	ft_init_env(&env_head, envp);
	shell->env_head = env_head;
	shell->cwd = getcwd(NULL, 0);
	ft_increment_shlvl(shell);
}
