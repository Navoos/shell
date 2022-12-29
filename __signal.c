/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machlouj <machlouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:41:56 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/13 14:33:39 by machlouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__sigint__(int __s)
{
	(void)__s;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_minishell.exit_status = 1;
}

void	__ignore__(int __s)
{
	if (__s == SIGINT)
		g_minishell.exit_status = 130;
	else if (__s == SIGQUIT)
		g_minishell.exit_status = 131;
}

void	__sigherd__(int __s)
{
	(void)__s;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_minishell.exit_status = 1;
	close(0);
}

void	__signal__main(void)
{
	signal(SIGINT, __sigint__);
	signal(SIGQUIT, SIG_IGN);
}

void	__history_main(char *cmd)
{
	ft_collect_tmp_mem(cmd);
	add_history(cmd);
}
