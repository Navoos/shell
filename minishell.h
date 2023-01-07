/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:50:52 by yakhoudr          #+#    #+#             */
/*   Updated: 2023/01/07 19:18:19 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_list
{
	DQUOTE_T,
	SQUOTE_T,
	DOLLAR_T,
	SREDIR_OUT_T,
	DREDIR_OUT_T,
	SREDIR_IN_T,
	HERDOC_T,
	PIPE_T,
	SQWORD_T,
	DQWORD_T,
	WORD_T,
	SPACE_T,
}	t_token_list;

typedef enum e_node_types
{
	RNODE,
	ENODE,
	PNODE,
}	t_node_types;

typedef struct s_memory
{
	void			*ptr;
	struct s_memory	*next;
}	t_memory;

typedef struct s_minishell
{
	int			error_flag;
	int			exit_status;
	t_memory	*tmp_memory;
	t_memory	*perm_memory;
	int			print_prompt;	
}	t_minishell;

typedef struct s_tokens
{
	int				type;
	char			*value;
	struct s_tokens	*next;
	struct s_tokens	*prev;
	int				herdoc_expandble;
}	t_tokens;

extern t_minishell		g_minishell;

// typedef struct s_env_list
// {
// 	char				*key;
// 	char				*value;
// 	char				**kv;
// 	struct s_env_list	*next;

// }	t_env_list;

typedef struct s_tree
{
	int	type;	
}	t_tree;

typedef struct s_cmd
{
	char			*val;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec_node
{
	int		type;
	t_cmd	*cmd;
}	t_exec_node;

typedef struct s_pipe_node
{
	int		type;
	t_tree	*left;
	t_tree	*right;
}	t_pipe_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_parser
{
	t_tokens	*current;
	t_env		*env_list;
	t_tree		*tree;
	t_tokens	*tokens;
}	t_parser;

typedef struct s_redir_node
{
	int			type;
	int			redir_type;
	int			fd;
	char		*file;
	int			flag;
	t_tree		*sub;
}	t_redir_node;

typedef struct s_path
{
	int		stat;
	char	*path;
}				t_path;

typedef struct s_shell
{
	t_env	*env_head;
	char	*cwd;
}				t_shell;

unsigned int	ft_wcount(char *s, char c);
int				ft_echo(int argc, char **argv);
void			ft_init_env(t_env **env_head, char **envp);
void			ft_init_shell(t_shell *shell, t_env *env_head, char **envp);
void			ft_add_env(t_env **env_head, char *key, char *value);
void			ft_delete_env(t_env **env_head, char *key);
void			ft_print_env(t_env *env_head);
char			*ft_get_env(t_env *env_head, char *key);
char			**ft_env_to_tab(t_env *env_head);
void			ft_export(t_shell *shell, char **args);
void			ft_unset(t_shell *shell, char **args);
void			ft_pwd(t_shell *shell);
void			ft_cd(t_shell *shell, char **args);
int				ft_exec_main(t_tree *tree, t_shell *shell);
void			ft_print_export(t_env *env_head);
int				ft_key_exist(t_env *env_head, char *key);
void			ft_exec_pipe(t_pipe_node *pnode, t_shell *shell);
void			ft_exit(char **args);
void			ft_redir(t_redir_node *redir_node, t_shell *shell);
char			**ft_get_args(t_cmd *cmd);
int				ft_get_argc(t_cmd *cmd);
void			ft_exec_signals(void);
void			ft_exec_cmd(t_shell *shell, char *_cmd, char **arglv,
					char **envp);
char			*get_path(t_env *env_head, char *cmd);
void			*ft_create_memory_node(void *ptr);
void			ft_add_to_perm_memory(t_memory	**memory, t_memory *new);
void			ft_add_to_tmp_memory(t_memory	**memory, t_memory *new);
void			*ft_create_memory_node(void *ptr);
void			ft_print_tokens(t_tokens *list);
unsigned int	ft_add_dquote(char *s, t_tokens **token);
unsigned int	ft_add_squote(char *s, t_tokens **token);
unsigned int	ft_add_dollar(char *s, t_tokens **token);
unsigned int	ft_add_space(char *s, t_tokens **token);
unsigned int	ft_add_word(char *s, t_tokens **token);
unsigned int	ft_add_pipe(char *s, t_tokens **token);
unsigned int	ft_add_in_redir(char *s, t_tokens **token);
unsigned int	ft_add_out_redir(char *s, t_tokens **token);
void			ft_push_back_token(t_tokens **head, t_tokens *new);
t_tokens		*ft_create_token(int type, char *value);
void			ft_tokenize_cmd(t_tokens **token,
					char *str, t_env *env_list);
int				ft_strcmp(char *s1, char *s2);
char			*ft_expand(char *str, t_env *env_list);
void			ft_merge_quoted_words(t_tokens **head, t_env *env_list);
t_tokens		*ft_merge_words(t_tokens *tmp,
					char **str, t_env *env_list);
t_tokens		*ft_merge_swords(t_tokens *tmp,
					char **str, t_env *env_list);
void			ft_check_syntax_redir(t_tokens *token);
void			ft_check_syntax_pipe(t_tokens *token);
void			ft_get_word(t_tokens *tmp, t_env *env_list, char **str);
t_tokens		*ft_merge_dwords(t_tokens *tmp,
					char **str, t_env *env_list);
t_tokens		*ft_get_prev_token(t_tokens *token);
t_tokens		*ft_get_next_token(t_tokens *token);
void			ft_get_exit_status(char **res, int *i);
int				ft_get_new_string(char *str, char **res, t_env *env_list);
int				ft_increase_normal_char(char *str, char **res);
void			__norm_ft_add_dqoute(char *str, t_tokens **token, int *i);
void			__norm_ft_tokenize_cmd(char *str, t_tokens **token, int *i);
void			__norm_ft_add_sqoute(char *str, t_tokens **token, int *i);
void			ft_print_tree(t_tree *tree, t_env **env);
char			*ft_strjoin_equal(char const *s1, char const *s2);
void			ft_drop_tmp_memory(void);
void			ft_drop_memory(void);
t_tree			*ft_construct_rnode(t_parser *parser, int flag, int fd);
int				ft_update_readline(void);
void			ft_handle_herdoc_sigint(int sig);
t_tree			*ft_construct_enode(void);
t_tree			*ft_construct_pnode(t_tree *left, t_tree *right);
t_tree			*ft_parse_exec(t_parser *parser);
t_tree			*ft_construct_herdoc(t_parser	*parser);
t_tree			*ft_parse_redir(t_parser *parser);
void			__print_tree(t_parser *parser, int io[2], t_tokens **token,
					t_shell *shell);
int				herdoc(t_parser	*parser);
void			*ft_collect_tmp_mem(void *ptr);
void			__signal__main(void);
void			__history_main(char *cmd);
t_tree			*ft_parse_cmd(t_parser *parser);
void			ft_is_merged(t_tokens **tmp,
					int merged, char **str, t_tokens *current);
t_tokens		*__norm_ft_merge_init(t_tokens *tmp);
void			inside_merge(t_tokens *tmp, char **str, t_tokens *current);
void			norm_tmp(char **tmp);
#endif
