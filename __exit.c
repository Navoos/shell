/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machlouj <machlouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:54:52 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/03 16:51:25 by machlouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__digit__(char __c)
{
	return (__c >= '0' && __c <= '9');
}

int	__status__(char **__s)
{
	int	__i;
	int	__j;

	__j = 1;
	while (__s[__j])
	{
		__i = 0;
		while (__s[__j][__i])
		{
			if (!__digit__(__s[__j][__i]))
			{
				printf("exit\n0usec: exit: %s: numeric argument required\n",
					__s[__i]);
				exit(2);
			}
			__i++;
		}
		if (__j > 1)
			return (printf("exit\n0usec: exit: too many arguments\n"), 1);
		__j++;
	}
	return (0);
}

int	__auth__(char **__s)
{
	if (!__s[1])
	{
		write(1, "exit\n", 5);
		exit(g_minishell.exit_status);
	}
	else if (__status__(__s))
	{
		g_minishell.exit_status = 1;
		return (0);
	}
	return (1);
}

void	__exit__(char **__s)
{
	if (__auth__(__s))
		return (g_minishell.exit_status = ft_atoi(__s[1]),
			exit(g_minishell.exit_status));
}
