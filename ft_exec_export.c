/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 20:24:55 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/09 13:14:50 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_sort_by_key(t_env *env_head)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*tmp_key;
	char	*tmp_value;

	tmp = env_head;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->key, tmp2->key) > 0)
			{
				tmp_key = tmp->key;
				tmp_value = tmp->value;
				tmp->key = tmp2->key;
				tmp->value = tmp2->value;
				tmp2->key = tmp_key;
				tmp2->value = tmp_value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (env_head);
}

void	ft_export_key_value(t_shell *shell, char **split, char **args, int i)
{
	g_minishell.exit_status = 0;
	if (!split[0][0])
		ft_print_env_error("export", args[i]);
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
		g_minishell.exit_status = 1;
	}
	else if (split[1])
		ft_add_env(&shell->env_head, split[0], split[1]);
	else if (args[i][ft_strlen(args[i]) - 1] == '=')
		ft_add_env(&shell->env_head, split[0], "");
	else
		ft_add_env(&shell->env_head, split[0], NULL);
}

void	ft_print_export(t_env *env_head)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = NULL;
	tmp = ft_copy_sorted_env(env_head);
	g_minishell.exit_status = 0;
	while (tmp[i])
	{
		ft_putstr_fd(tmp[i], 1);
		i++;
	}
	ft_free_args(tmp);
}

char	**ft_split_f_occ(char *str, char c, t_env *env_head)
{
	int		i;
	char	**split;

	i = -1;
	split = ft_xalloc(sizeof(char *) * 3);
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

void	ft_export(t_shell *shell, char **args)
{
	int		i;
	char	**split;

	i = 1;
	if (!args[1] || ft_strcmp(args[1], "#") == 0)
	{
		ft_print_export(shell->env_head);
		return ;
	}
	while (args[i])
	{
		split = ft_split_f_occ(args[i], '=', shell->env_head);
		ft_export_key_value(shell, split, args, i);
		i++;
		ft_free_args(split);
	}
}
