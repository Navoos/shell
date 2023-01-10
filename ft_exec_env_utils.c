/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 23:27:22 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/10 17:57:42 by mzridi           ###   ########.fr       */
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

void	ft_print_env_error(char *cmd, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_minishell.exit_status = 1;
}

char	**ft_env_to_tab(t_env *env_head)
{
	t_env	*tmp;
	char	**envp;
	int		i;
	char	*tmp_key;

	tmp = env_head;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = ft_xalloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = env_head;
	while (tmp)
	{
		tmp_key = ft_strjoin(tmp->key, "=");
		envp[i] = ft_strjoin(tmp_key, tmp->value);
		free(tmp_key);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	ft_remove_key(t_env **env_head, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env_head;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env_head = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
