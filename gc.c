/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:45:44 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/10/10 12:54:57 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_xalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("ERROR : Malloc failed to allocate memory", STDERR_FILENO);
		exit(96);
	}
	return (ptr);
}

void	*ft_collect_tmp_mem(void	*ptr)
{
	t_memory	*mem;

	mem = ft_xalloc(sizeof(t_memory));
	mem->ptr = ptr;
	mem->next = 0x0;
	ft_add_to_tmp_memory(&g_minishell.tmp_memory, mem);
	return (ptr);
}

void	*ft_create_memory_node(void *ptr)
{
	t_memory	*mem;

	mem = (ft_xalloc(sizeof(t_memory)));
	mem->ptr = ptr;
	mem->next = 0x0;
	return (mem);
}

void	ft_add_to_perm_memory(t_memory	**memory, t_memory *new)
{
	t_memory	*tmp;

	if (!*memory)
	{
		*memory = new;
		return ;
	}
	tmp = *memory;
	while (tmp)
	{
		if (tmp->ptr == new->ptr)
		{
			free(new);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = *memory;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	ft_add_to_tmp_memory(t_memory	**memory, t_memory *new)
{
	t_memory	*tmp;

	if (!*memory)
	{
		*memory = new;
		return ;
	}
	tmp = *memory;
	while (tmp)
	{
		if (tmp->ptr == new->ptr)
		{
			free(new);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = *memory;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}
