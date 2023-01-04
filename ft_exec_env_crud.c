/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env_crud.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:39:12 by mzridi            #+#    #+#             */
/*   Updated: 2022/12/31 23:27:54 by mzridi           ###   ########.fr       */
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
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_add_env(t_env **env_head, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env_head;
	if (!*env_head)
	{
		*env_head = malloc(sizeof(t_env));
		(*env_head)->key = key;
		(*env_head)->value = value;
		(*env_head)->next = NULL;
		return ;
	}
	if (ft_update_env(env_head, key, value))
		return ;
	while (tmp->next)
		tmp = tmp->next;
	new = malloc(sizeof(t_env));
	new->key = key;
	new->value = value;
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
