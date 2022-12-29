/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:13:52 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/10 12:52:44 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isalpha_or_(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' )
		return (1);
	return (0);
}

int	__check__export(char **__s, t_env_list **__env)
{
	int	i;

	i = 1;
	while (__s[i])
	{
		if (__equal__(__s[i]))
		{
			if (__check__(__s[i]))
				__insert__(__s[i], __env);
		}
		else if (__check_2__(__s[i]))
		{
			__insert__(__s[i], __env);
		}
		i++;
	}
	return (1);
}

void	norm_insert(char *s, char **k, char **v)
{
	if (__equal__(s))
	{
		*k = (ft_strdup(s));
		*v = NULL;
	}
	else
	{
		*k = ft_strndup(s, ft_strchr(s, '=') - s);
		*v = ft_strndup(ft_strchr(s, '=')
				+ 1, ft_strrchr(s, 0) - ft_strchr(s, '=') - 1);
	}
}

void	__insert__(char *__s, t_env_list **__env)
{
	char		*key__;
	char		*val__;
	t_env_list	*tmp_env;

	key__ = 0x0;
	val__ = 0x0;
	tmp_env = *__env;
	norm_insert(__s, &key__, &val__);
	while (tmp_env)
	{
		if (tmp_env && !ft_strcmp((char *) key__, tmp_env->key))
		{
			free(key__);
			free(tmp_env->value);
			tmp_env->value = val__;
			return ;
		}
		if (tmp_env)
			tmp_env = tmp_env->next;
	}
	ft_add_env_entrace(__env, ft_create_env_node(key__, val__));
}

void	__export__(char **__s, t_env_list **__env)
{
	if (!__env)
		return ;
	if (!__s[1])
		__sort_export__(__env);
	else
		__check__export(__s, __env);
	g_minishell.exit_status = 0;
}
