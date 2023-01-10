/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 20:09:29 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/09 16:07:21 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args)
{
	if (args[1] == NULL || !args)
	{
		ft_putstr_fd("exit\n", 1);
		exit(g_minishell.exit_status);
	}
	else if (!ft_isnumber(args[1]) || strlen(args[1]) > 19 || (strlen(args[1])
			== 19 && ft_strcmp(args[1], "9223372036854775807") > 0))
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("bigshell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else if (args[2] != NULL)
	{
		ft_putstr_fd("bigshell: exit: too many arguments\n", 2);
		ft_putstr_fd("exit\n", 1);
		g_minishell.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		exit(ft_atoi(args[1]));
	}
}
