/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:17:28 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/10/10 14:30:09 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_buffer(char *buffer)
{
	if (buffer)
	{
		ft_collect_tmp_mem(buffer);
	}
}

char	*expand_buffer(char *buffer, t_parser *parser)
{
	buffer = ft_expand(buffer, parser->env_list);
	ft_collect_tmp_mem(buffer);
	return (buffer);
}

int	herdoc(t_parser	*parser)
{
	char	*buffer;
	int		pi[2];

	if (!parser->current->next->value || pipe(pi) == -1)
		exit(666);
	signal(SIGINT, ft_handle_herdoc_sigint);
	while (1)
	{
		buffer = readline("> ");
		if (!buffer || (buffer && !*buffer && g_minishell.error_flag))
			break ;
		if (!ft_strcmp(buffer, parser->current->next->value))
		{
			if_buffer(buffer);
			break ;
		}
		ft_collect_tmp_mem(buffer);
		if (parser->current->next->herdoc_expandble)
			buffer = expand_buffer(buffer, parser);
		write(pi[1], buffer, ft_strlen(buffer));
		write(pi[1], "\n", 1);
	}
	return (close(pi[1]), pi[0]);
}

t_tree	*ft_parse_pipe(t_parser *parser)
{
	t_tree		*right;
	t_tree		*left;

	left = ft_parse_exec(parser);
	while (parser->current && parser->current->type == PIPE_T)
	{
		parser->current = parser->current->next;
		right = ft_parse_exec(parser);
		left = ft_construct_pnode(left, right);
	}
	parser->tree = left;
	return (parser->tree);
}

t_tree	*ft_parse_cmd(t_parser *parser)
{
	return (ft_parse_pipe(parser));
}
