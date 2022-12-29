/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:40:29 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/10 12:50:26 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__check_key__(char *key, t_env_list *__env)
{
	while (__env)
	{
		if (!ft_strcmp(__env->key, key))
			return (1);
		__env = __env->next;
	}
	return (0);
}

void	__init_remove__(t_env_list **__rm, t_env_list **__cr,
t_env_list **tmp, t_env_list **__env)
{
	*__rm = *__env;
	*__cr = *__env;
	*tmp = *__env;
}

void	ft_unset_var(t_env_list *var)
{
	free((var)->key);
	free((var)->value);
	free((var));
	((var)->key) = 0x0;
	((var)->value) = 0x0;
}

void	__remove__(char *__s, t_env_list **__env)
{
	t_env_list	*__rm;
	t_env_list	*__cr;
	t_env_list	*tmp;

	__init_remove__(&__rm, &__cr, &tmp, __env);
	if (__env && !ft_strcmp(tmp->key, __s))
	{
		*__env = (*__env)->next;
		ft_unset_var(__rm);
		return ;
	}
	while (__cr)
	{
		if (__cr->next && !ft_strcmp(__cr->next->key, __s))
		{
			__rm = __cr->next;
			__cr->next = __cr->next->next;
			ft_unset_var(__rm);
			return ;
		}
		__cr = __cr->next;
	}
}

void	__unset__(char **__s, t_env_list **__env)
{
	int	__i;

	__i = 1;
	if (__s)
	{
		while (__s[__i])
		{
			if (__check_key__(__s[__i], *__env))
				__remove__(__s[__i], __env);
			__i++;
		}
	}
	g_minishell.exit_status = 0;
}
