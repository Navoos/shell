/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:32:55 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/10/09 14:20:33 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tokens(t_tokens *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("<%s>\t%d\n", list->value, list->type);
		if (list->herdoc_expandble)
			printf("herdoc expandble\n");
		else
			printf("NOT herdoc expandble\n");
		list = list->next;
		i += 1;
	}
	printf("tokens count : %d\n", i);
}
