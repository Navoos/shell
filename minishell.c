/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:51:08 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/12/30 21:10:13 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <readline/history.h>
#include <signal.h>
#include <sys/fcntl.h>
#include <unistd.h>

t_minishell	g_minishell;

void	__init__(t_parser *parser, int io[2])
{
	rl_event_hook = ft_update_readline;
	rl_catch_signals = 0;
	rl_done = 0;
	rl_outstream = stderr;
	parser->tree = 0x0;
	parser->current = 0x0;
	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
}

void	__error_flag(int io[2], t_tokens **token)
{
	ft_drop_tmp_memory();
	*token = 0x0;
	g_minishell.error_flag = 0;
	dup2(io[0], STDIN_FILENO);
	dup2(io[1], STDOUT_FILENO);
}

void	ft_run_shell(char **envp)
{
	char				*cmd;
	t_parser			parser;
	int					io[2];

	__init__(&parser, io);
	ft_init_env_list(&parser.env_list, envp);
	parser.tokens = 0x0;
	while (1)
	{
		__signal__main();
		cmd = readline("0usec$ ");
		if (!cmd)
			break ;
		__history_main(cmd);
		ft_tokenize_cmd(&parser.tokens, cmd, parser.env_list);
		if (g_minishell.error_flag)
		{
			__error_flag(io, &parser.tokens);
			continue ;
		}
		parser.current = parser.tokens;
		parser.tree = ft_parse_cmd(&parser);
		while (((t_exec_node *)parser.tree)->cmd)
		{
			printf("%s ", ((t_exec_node *)parser.tree)->cmd->val);
			(((t_exec_node *)parser.tree))->cmd = ((t_exec_node *)parser.tree)->cmd->next;
		}
		printf("\n");
		__print_tree(&parser, io, &parser.tokens);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("ERROR : Can't run Minishell with arguments",
			STDERR_FILENO);
		return (69);
	}
	ft_run_shell(envp);
	return (g_minishell.exit_status);
}

// void	__print_tree(t_parser *parser, int io[2], t_tokens **token)
// {
// 	ft_print_tree(parser->tree, &parser->env_list);
// 	ft_drop_tmp_memory();
// 	if (token)
// 		*token = 0x0;
// 	g_minishell.error_flag = 0;
// 	dup2(io[0], STDIN_FILENO);
// 	dup2(io[1], STDOUT_FILENO);
// }
