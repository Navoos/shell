/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 20:09:29 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/02 20:28:03 by mzridi           ###   ########.fr       */
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
	if (args[1] == NULL)
	{
		printf("exit\n");
		exit(g_minishell.exit_status);
	}
	else if (!ft_isnumber(args[1]))
	{
		printf("exit\n");
		printf("bigshell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	else if (args[2] != NULL)
	{
		printf("exit\n");
		printf("bigshell: exit: too many arguments\n");
		g_minishell.exit_status = 1;
	}
	else
	{
		printf("exit\n");
		exit(ft_atoi(args[1]));
	}
}
	