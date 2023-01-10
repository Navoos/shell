/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env_crud.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:39:12 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/10 12:17:16 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_env(t_env **env_head, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env_head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (!value)
				return (1);
			free(tmp->value);
			tmp->value = ft_strdup(value);
			ft_add_to_perm_memory(&g_minishell.perm_memory,
				ft_create_memory_node(tmp->value));
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_create_env_head(t_env **env_head, char *key, char *value)
{
	*env_head = ft_xalloc(sizeof(t_env));
	ft_add_to_perm_memory(&g_minishell.perm_memory,
		ft_create_memory_node(*env_head));
	(*env_head)->key = ft_strdup(key);
	ft_add_to_perm_memory(&g_minishell.perm_memory,
		ft_create_memory_node((*env_head)->key));
	(*env_head)->value = ft_strdup(value);
	ft_add_to_perm_memory(&g_minishell.perm_memory,
		ft_create_memory_node((*env_head)->value));
	(*env_head)->next = NULL;
}

void	ft_add_env(t_env **env_head, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env_head;
	if (!*env_head)
	{
		ft_create_env_head(env_head, key, value);
		return ;
	}
	if (ft_update_env(env_head, key, value))
		return ;
	while (tmp->next)
		tmp = tmp->next;
	new = ft_xalloc(sizeof(t_env));
	ft_add_to_perm_memory(&g_minishell.perm_memory,
		ft_create_memory_node(new));
	new->key = ft_strdup(key);
	ft_add_to_perm_memory(&g_minishell.perm_memory,
		ft_create_memory_node(new->key));
	new->value = ft_strdup(value);
	ft_add_to_perm_memory(&g_minishell.perm_memory,
		ft_create_memory_node(new->value));
	new->next = NULL;
	tmp->next = new;
}

void	ft_delete_env(t_env **env_head, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	if (!*env_head)
		return ;
	tmp = (*env_head)->next;
	prev = *env_head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			prev->next = tmp->next;
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

char	*ft_get_env(t_env *env_head, char *key)
{
	t_env	*tmp;

	tmp = env_head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
