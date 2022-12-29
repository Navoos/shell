/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machlouj <machlouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:25:46 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/14 11:47:37 by machlouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*__path__(t_env_list *__path, char *___s)
{
	while (__path)
	{
		if (__path && !ft_strcmp(__path->key, ___s))
			return (__path->value);
		__path = __path->next;
	}
	return (NULL);
}

void	__change__(t_env_list *__env, char *__new, char *__old)
{
	char	*__path;
	void	*__dir;
	char	*__dlt;

	__dlt = "DELETED";
	__path = 0x0;
	if (chdir(__new) == -1)
		return ;
	__path = ft_collect_tmp_mem(malloc(sizeof(char) * 255));
	if (!__path)
	{
		perror("ERROR");
		exit(1);
	}
	if (getcwd((__path), 255) == NULL)
		write(2, "cd: error retrieving current directory\n", 40);
	__dir = (opendir(__old));
	if (!__dir)
		__update__(__env, __path, __dlt);
	else
	{
		__update__(__env, __path, __old);
		closedir(__dir);
	}
	g_minishell.exit_status = 0;
}

void	__update__(t_env_list *__env, char *__new, char *__old)
{
	while (__env)
	{
		if (__env->key && !ft_strcmp(__env->key, "OLDPWD"))
		{
			if (__env->value)
			{
				free(__env->value);
				__env->value = (ft_strdup
						((__old)));
			}
		}
		if (__env->key && !ft_strcmp(__env->key, "PWD"))
		{
			if (__env->value)
			{
				free(__env->value);
				__env->value = (ft_strdup((__new)));
			}
		}
		__env = __env->next;
	}
}

int	__check__directory(char **__s, t_env_list *__env, char *__c)
{
	int		__i;
	char	*__p;

	__p = 0x0;
	__i = 1;
	if (!__s[1])
	{
		__p = __path__(__env, "HOME");
		if (!__p)
			return (printf("0usec: cd: HOME not set\n"),
				g_minishell.exit_status = 1, 0);
		else
			return (__change__(__env, __p, __c), 0);
	}
	else if (__s[2])
		return (printf("0usec: cd: too many arguments\n"), 0);
	return (1);
}

int	__cd__(char **__s, t_env_list **__env)
{
	char	*__i;

	__i = 0x0;
	__i = ft_collect_tmp_mem(malloc(sizeof(char) * 255));
	if (!__i)
	{
		perror("ERROR");
		exit(1);
	}
	(getcwd((__i), 255));
	if (__check__directory(__s, *__env, __i))
		if (__dir__(__s))
			__change__(*__env, __s[1], __i);
	return (0);
}
