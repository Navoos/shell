/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 23:27:22 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/04 21:29:43 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_key_exist(t_env *env_head, char *key)
{
	t_env	*tmp;

	tmp = env_head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_print_env(t_env *env_head)
{
	t_env	*tmp;

	tmp = env_head;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
}

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

void	ft_print_export(t_env *env_head)
{
	t_env	*tmp;

	tmp = ft_sort_by_key(env_head);
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	free(tmp);
}

char	**ft_env_to_tab(t_env *env_head)
{
	t_env	*tmp;
	char	**envp;
	int		i;

	tmp = env_head;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = env_head;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->key, "=");
		envp[i] = ft_strjoin(envp[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
