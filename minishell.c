/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:51:08 by yakhoudr          #+#    #+#             */
/*   Updated: 2023/01/10 19:20:12 by mzridi           ###   ########.fr       */
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

void	ft_run_shell(t_shell *shell)
{
	char				*cmd;
	t_parser			parser;
	int					io[2];

	__init__(&parser, io);
	parser.env_list = shell->env_head;
	parser.tokens = 0x0;
	while (1)
	{
		g_minishell.print_prompt = 1;
		ft_exec_signals();
		cmd = readline("bigshell$ ");
		add_history(cmd);
		if (ft_add_command_to_mem(cmd) == -1)
			ft_exit(NULL);
		ft_tokenize_cmd(&parser.tokens, cmd, shell->env_head);
		if (g_minishell.error_flag)
		{
			__error_flag(io, &parser.tokens);
			continue ;
		}
		parser.current = parser.tokens;
		parser.tree = ft_parse_cmd(&parser);
		__print_tree(&parser, io, &parser.tokens, shell);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_shell	*shell;

	(void)av;
	shell = malloc(sizeof(t_shell));
	g_minishell.exit_status = 0;
	env = NULL;
	ft_init_shell(shell, env, envp);
	if (ac != 1)
	{
		ft_putstr_fd("ERROR : Can't run Minishell with arguments",
			STDERR_FILENO);
		return (69);
	}
	ft_run_shell(shell);
	return (g_minishell.exit_status);
}

void	__print_tree(t_parser *parser, int io[2],
						t_tokens **token, t_shell *shell)
{	
	g_minishell.is_child = 1;
	ft_exec_main(parser->tree, shell);
	if (g_minishell.exit_status == 131)
		ft_putstr_fd("Quit: 3\n", 2);
	g_minishell.is_child = 0;
	ft_drop_tmp_memory();
	if (token)
		*token = 0x0;
	dup2(io[0], STDIN_FILENO);
	dup2(io[1], STDOUT_FILENO);
}
