/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 22:31:46 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/02 20:05:15 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**ft_split_f_occ(char *str, char c, t_env *env_head)
{
	int		i;
	char	**split;

	i = -1;
	split = malloc(sizeof(char *) * 3);
	split[2] = NULL;
	while (str[++i])
	{
		if (str[i] == c)
		{
			if (i > 1 && str[i - 1] == '+')
			{
				split[0] = ft_substr(str, 0, i - 1);
				split[1] = ft_strjoin(ft_get_env(env_head, split[0]), \
							ft_substr(str, i + 1, ft_strlen(str) - i));
				return (split);
			}
			split[0] = ft_substr(str, 0, i);
			split[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
			return (split);
		}
	}
	split[0] = ft_substr(str, 0, i);
	split[1] = NULL;
	return (split);
}

void	ft_export_key_value(t_shell *shell, char **split, char **args, int i)
{
	if (!split[0][0])
	{
		ft_putstr_fd("bigshell: export: `", 2);
		ft_putstr_fd(args[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else if (!ft_is_valid_env(split[0]))
	{
		ft_putstr_fd("bigshell: export: `", 2);
		ft_putstr_fd(split[0], 2);
		ft_putstr_fd("=", 2);
		if (split[1])
		{
			ft_putstr_fd(split[1], 2);
		}
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else if (split[1])
		ft_add_env(&shell->env_head, split[0], split[1]);
	else if (args[i][ft_strlen(args[i]) - 1] == '=')
		ft_add_env(&shell->env_head, split[0], "");
	else
		ft_add_env(&shell->env_head, split[0], NULL);
}

void	ft_export(t_shell *shell, char **args)
{
	int		i;
	char	**split;

	i = 1;
	if (!args[1])
	{
		ft_print_export(shell->env_head);
		return ;
	}
	while (args[i])
	{
		split = ft_split_f_occ(args[i], '=', shell->env_head);
		ft_export_key_value(shell, split, args, i);
		i++;
	}
}

void	ft_unset(t_shell *shell, char **args)
{
	int		i;

	i = 1;
	if (!args[1])
		return ;
	if (!args[i][0])
	{
		ft_putstr_fd("bigshell: unset: `", 2);
		ft_putstr_fd(args[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
	while (args[i])
	{
		if (!args[i][0] || !ft_is_valid_env(args[i]))
		{
			ft_putstr_fd("bigshell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
			ft_delete_env(&shell->env_head, args[i]);
		i++;
	}
}
