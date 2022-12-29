/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machlouj <machlouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:13:24 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/06 18:09:13 by machlouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__verify__builtin__(char **__s)
{
	if (!ft_strcmp(__s[0], "echo"))
		return (1);
	else if (!ft_strcmp(__s[0], "pwd"))
		return (1);
	else if (!ft_strcmp(__s[0], "export"))
		return (1);
	else if (!ft_strcmp(__s[0], "unset"))
		return (1);
	else if (!ft_strcmp(__s[0], "cd"))
		return (1);
	else if (!ft_strcmp(__s[0], "env"))
		return (1);
	else if (!ft_strcmp(__s[0], "exit"))
		return (1);
	return (0);
}

void	__builtin__(char **__s, t_env_list **__env)
{
	if (!ft_strcmp(__s[0], "echo"))
		__echo__(__s);
	else if (!ft_strcmp(__s[0], "pwd"))
		__pwd__();
	else if (!ft_strcmp(__s[0], "cd"))
		__cd__(__s, __env);
	else if (!ft_strcmp(__s[0], "env"))
		__env__(__env, __s);
	else if (!ft_strcmp(__s[0], "exit"))
		__exit__(__s);
	else if (!ft_strcmp(__s[0], "export"))
		__export__(__s, __env);
	else if (!ft_strcmp(__s[0], "unset"))
		__unset__(__s, __env);
}

int	__find_index(char *__s, char __f)
{
	int	i;

	i = 0;
	if (!__s)
		return (-1);
	while (__s[i])
	{
		if (__s[i] == __f)
			return (i);
		i += 1;
	}
	return (-1);
}
