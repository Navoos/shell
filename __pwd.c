/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:11:35 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/09 21:52:35 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__pwd__output__(char *__s)
{
	int	i;

	i = 0;
	if (__s)
	{
		while (__s[i])
			write(1, &__s[i++], 1);
	}
	write(1, "\n", 1);
}

void	__pwd__(void)
{
	char	*tmp;

	tmp = ft_collect_tmp_mem(getcwd(0x0, 0));
	if (!tmp)
		return ;
	__pwd__output__(tmp);
	g_minishell.exit_status = 0;
}
