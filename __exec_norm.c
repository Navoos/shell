/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exec_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:07:16 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/12/30 11:52:00 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**__norm_ft_mod_split_arg(char *cmd, char *arg)
{
	char	**ret;

	ret = 0x0;
	ret = ft_collect_tmp_mem(ft_xalloc(sizeof(char *) * 3));
	ret[0] = (cmd);
	ret[1] = (arg);
	ret[2] = 0x0;
	return (ret);
}

char	**__norm_ft_mod_split_no_arg(char *cmd)
{
	char	**ret;

	ret = 0x0;
	ret = ft_collect_tmp_mem(ft_xalloc(sizeof(char *) * 2));
	ret[0] = (cmd);
	ret[1] = 0x0;
	return (ret);
}

void	__error_norm(char *cmd)
{
	printf("0usec: %s: command not found\n", cmd);
	g_minishell.exit_status = 127;
	exit(127);
}

// int	__error__(char **__s, t_env_list *__env)
// {
// 	int	i;

// 	i = 0;
// 	if (__accept__(__s))
// 		return (__exec__v1(__s, __env));
// 	else
// 		return (__exec__v2(__s, __env));
// 	return (0);
// }
