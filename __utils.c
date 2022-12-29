/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:02:20 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/09 22:53:55 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__dir__(char **__s)
{
	void	*__dir;

	__dir = (opendir(__s[1]));
	if (!__dir)
	{
		if (ENOENT)
			return (printf("0usec: cd: %s: No such file or directory\n", __s[1]),
				g_minishell.exit_status = 1, 0);
		else if (EACCES)
			return (printf("0usec: cd: %s/: Permission denied\n", __s[1]),
				g_minishell.exit_status = 1, 0);
		else if (ENOTDIR)
			return (printf("0usec: cd: %s: Not a directory\n", __s[1]),
				g_minishell.exit_status = 1, 0);
	}	
	closedir(__dir);
	return (1);
}

int	__accept__(char **__s)
{
	if ((__s[0][0] == '.' && __s[0][1] == '/') ||
		__s[0][0] == '/' || __s[0][0] == '~')
		return (1);
	return (0);
}

char	*__access__(char **__s)
{
	char	*__v;

	if (access(__s[0], X_OK) == 0)
		return (__v = ft_collect_tmp_mem(ft_strdup(__s[0])), __v);
	return (NULL);
}
