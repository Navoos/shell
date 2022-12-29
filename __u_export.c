/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __u_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machlouj <machlouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:34:21 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/02 15:34:22 by machlouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__cmp_char__(char s, char d)
{
	return (s - d);
}

void	__print_export__(t_env_list *__env, char i)
{
	(void)i;
	while (__env)
	{
		if (__env->value && __env->key && !__cmp_char__(__env->key[0], i))
			printf("declare -x %s=\"%s\"\n", __env->key, __env->value);
		else if (__env && !__env->value
			&& __env->key && !__cmp_char__(__env->key[0], i))
			printf("declare -x %s\n", __env->key);
		__env = __env->next;
	}
}

void	__sort_export__(t_env_list **__env)
{
	char	i;

	i = 'A';
	while (i <= 'Z')
		__print_export__(*__env, i++);
	i = 'a';
	while (i <= 'z')
		__print_export__(*__env, i++);
	__print_export__(*__env, '_');
	g_minishell.exit_status = 0;
}

int	__equal__(char *__s)
{
	int	i;

	i = 0;
	if (__s[i] == '=')
		return (printf("0usec: export: `%s': not a valid identifier\n", __s), 0);
	while (__s[i])
	{
		if (__s[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	___check_kara__(char *__c)
{
	int	i;

	i = 0;
	while (__c[i])
	{
		if ((__c[i] >= 'A' && __c[i] <= 'Z')
			|| (__c[i] == '=' || __c[i] == '_')
			|| (__c[i] >= 'a' && __c[i] <= 'z') || ft_isdigit(__c[i]))
			i++;
		else
			return (0);
	}
	return (1);
}
