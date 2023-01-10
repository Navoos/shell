/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:16:34 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/10 17:45:54 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_prompt(void)
{
	write(1, "\n", 1);
	if (g_minishell.print_prompt && !g_minishell.is_child)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_minishell.exit_status = 1;
}

void	ft_exec_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "", 1);
		ft_exec_prompt();
	}
}

void	ft_exec_signals(void)
{
	g_minishell.print_prompt = 1;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_exec_sigint);
}
