/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 22:31:46 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/10 19:10:42 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_len(t_env *env_head)
{
	int	i;

	i = 0;
	while (env_head)
	{
		i++;
		env_head = env_head->next;
	}
	return (i);
}

void	ft_concat_key_value(t_env *env_head, char **env)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	while (env_head)
	{
		tmp = ft_strjoin("declare -x ", env_head->key);
		if (env_head->value)
		{
			tmp2 = ft_strjoin(tmp, "=");
			free(tmp);
			tmp = ft_strjoin(tmp2, "\"");
			free(tmp2);
			tmp2 = ft_strjoin(tmp, env_head->value);
			free(tmp);
			tmp = ft_strjoin(tmp2, "\"");
			free(tmp2);
		}
		tmp2 = ft_strjoin(tmp, "\n");
		free(tmp);
		env[i++] = tmp2;
		env_head = env_head->next;
	}
}

char	**ft_copy_sorted_env(t_env *env_head)
{
	char	**env;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	env = (char **)ft_xalloc(sizeof(char *) * (ft_env_len(env_head) + 1));
	ft_concat_key_value(env_head, env);
	env[ft_env_len(env_head)] = NULL;
	i = -1;
	while (env[++i])
	{
		j = i ;
		while (env[++j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
		}
	}
	return (env);
}

int	ft_is_valid_env(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(t_shell *shell, char **args)
{
	int		i;

	i = 1;
	g_minishell.exit_status = 0;
	if (!args[1])
		return ;
	if (!args[i][0])
	{
		ft_print_env_error(args[0], args[i]);
		return ;
	}
	while (args[i])
	{
		if (ft_strcmp(args[i], "OLDPWD") == 0)
			g_minishell.oldpwd = 0;
		if (ft_strcmp(args[i], "PWD") == 0 || ft_strcmp(args[i], "SHLVL"))
			ft_remove_key(&shell->env_head, args[i]);
		else if (!args[i][0] || !ft_is_valid_env(args[i]))
			ft_print_env_error(args[0], args[i]);
		else
			ft_delete_env(&shell->env_head, args[i]);
		i++;
	}
}
