/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __execv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machlouj <machlouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:55:15 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/13 19:56:28 by machlouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__exec__v1(char **__s, t_env_list *__env)
{
	char	**check;
	int		i;

	i = 0;
	if (__s[1])
	{
		check = ft_split(ft_collect_tmp_mem(ft_strjoin(
						ft_collect_tmp_mem(ft_strjoin(__s[0], " ")),
						__s[1])), ' ');
		ft_collect_tmp_mem(check);
		while (check[i])
			ft_collect_tmp_mem(check[i++]);
		if (execve(__access__(__s), check, env_path(__env)) == -1)
			return (1);
	}
	if (execve(__access__(__s), __s, env_path(__env)) == -1)
		return (1);
	return (0);
}

int	__exec__v2(char **__s, t_env_list *__env)
{
	int		i;
	char	**check;

	i = 0;
	if (__s[1])
	{
		check = ft_split(ft_collect_tmp_mem(ft_strjoin(
						ft_collect_tmp_mem(ft_strjoin(__s[0], " ")),
						__s[1])), ' ');
		ft_collect_tmp_mem(check);
		while (check[i])
			ft_collect_tmp_mem(check[i++]);
		if (execve(__execv__(__s, __env), check, env_path(__env)) == -1)
			return (1);
	}
	if (execve(__execv__(__s, __env), __s, env_path(__env)) == -1)
		return (1);
	return (0);
}
