/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:52:25 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/12 15:28:02 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__output__(char *__s, bool newline)
{
	int	i;

	i = 0;
	if (__s)
	{
		while (__s[i])
		{
			write(1, &__s[i], 1);
			i++;
		}
	}
	if (newline)
		write(1, "\n", 1);
}

int	__check__flag(char **__s)
{
	int	i;

	i = 0;
	while (__s[1][i])
	{
		if (__s[1][i] == '-' && i == 0)
		{
			i += 1;
			while (__s[1][i] == 'n')
				i += 1;
			if (__s[1][i] != ' ' && __s[1][i] != 0)
				return (0);
			else
				return (1);
		}
		else
			i += 1;
	}
	return (0);
}

char	*__skip__(char **__s)
{
	int	i;

	i = 0;
	if (__s[1][i] == '-')
	{
		i += 1;
		while (__s[1][i] == 'n')
			i += 1;
		if (__s[1][i] != ' ' && __s[1][i] != 0)
			return (__s[1]);
		else
			return (&__s[1][i + 1]);
	}
	return (__s[1]);
}

void	__echo__(char **__s)
{
	char	*tmp;

	if (!__s[1])
		return (__output__(0x0, true));
	if (__check__flag(__s))
		return (tmp = __skip__(__s), __output__(tmp, false));
	else
		__output__(__s[1], true);
	g_minishell.exit_status = 0;
}
