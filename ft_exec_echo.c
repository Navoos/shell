/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:38:27 by mzridi            #+#    #+#             */
/*   Updated: 2022/12/30 21:29:17 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

int	skip_n(int argc, char **args)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc && args[i][0] == '-' && args[i][1] && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][j])
		{
			if (args[i][j] == 'n')
				j++;
			else
				break ;
		}
		if (!args[i][j])
			i++;
		else
			break ;
	}
	return (i);
}

int	ft_echo(int argc, char **argv)
{
	int	i;
	int	n;

	i = skip_n(argc, argv);
	n = 0;
	if (i > 1)
		n = 1;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	return (0);
}
