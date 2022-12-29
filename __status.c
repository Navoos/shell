/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __status.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machlouj <machlouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:08:46 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/12 22:28:35 by machlouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__signal__status__(int __i)
{
	if (WTERMSIG(__i) == 2)
	{
		write(1, "\n", 1);
		g_minishell.exit_status = 130;
	}
	if (WTERMSIG(__i) == 3)
	{
		write(1, "Quit: 3\n", 9);
		g_minishell.exit_status = 131;
	}
}

void	__signal__(void)
{
	signal(SIGINT, __ignore__);
	signal(SIGQUIT, __ignore__);
}
