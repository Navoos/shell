/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:50:52 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/12/30 11:02:59 by yakhoudr         ###   ########.fr       */
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

typedef struct s_env_list
{
	char				*key;
	char				*value;
	char				**kv;
	struct s_env_list	*next;

}	t_env_list;

typedef struct s_tree
{
	int	type;	
}	t_tree;

typedef struct s_cmd
{
	char	*val;
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

typedef struct s_parser
{
	t_tokens	*current;
	t_env_list	*env_list;
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

void			ft_init_env_list(t_env_list **env, char **envp);
void			*ft_create_memory_node(void *ptr);
void			ft_add_to_perm_memory(t_memory	**memory, t_memory *new);
void			ft_add_to_tmp_memory(t_memory	**memory, t_memory *new);
void			ft_print_env_list(t_env_list *list);
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
					char *str, t_env_list *env_list);
int				ft_strcmp(char *s1, char *s2);
char			*ft_expand(char *str, t_env_list *env_list);
void			ft_merge_quoted_words(t_tokens **head, t_env_list *env_list);
t_tokens		*ft_merge_words(t_tokens *tmp,
					char **str, t_env_list *env_list);
t_tokens		*ft_merge_swords(t_tokens *tmp,
					char **str, t_env_list *env_list);
void			ft_check_syntax_redir(t_tokens *token);
void			ft_check_syntax_pipe(t_tokens *token);
void			ft_get_word(t_tokens *tmp, t_env_list *env_list, char **str);
t_tokens		*ft_merge_dwords(t_tokens *tmp,
					char **str, t_env_list *env_list);
t_tokens		*ft_get_prev_token(t_tokens *token);
t_tokens		*ft_get_next_token(t_tokens *token);
void			ft_get_exit_status(char **res, int *i);
int				ft_get_new_string(char *str, char **res, t_env_list *env_list);
int				ft_increase_normal_char(char *str, char **res);
void			__norm_ft_add_dqoute(char *str, t_tokens **token, int *i);
void			__norm_ft_tokenize_cmd(char *str, t_tokens **token, int *i);
void			__norm_ft_add_sqoute(char *str, t_tokens **token, int *i);
char			*__skip__(char **__s);
void			__echo__(char **__s);
void			s__exec__(t_exec_node *__cmd, t_env_list **__env);
void			__exec__(char **__cmd, t_env_list **__env);
char			*__valid__path(t_env_list *__env);
char			*__access__(char **__s);
char			*__execv__(char **__s, t_env_list *__env);
int				__error__(char **__s, t_env_list *__env);
void			__ignore__(int __s);
void			__sigint__(int __s);
void			__signal__status__(int __i);
void			__signal__(void);
void			__sigherd__(int __s);
void			__builtin__(char **__s, t_env_list **__env);
int				__verify__builtin__(char **__s);
void			__pwd__(void);
void			__pwd__output__(char *__s);
int				__cd__(char **__s, t_env_list **__env);
void			__update__(t_env_list *__env, char *__new, char *__old);
int				__dir__(char **__s);
void			__env__(t_env_list **__env, char **__s);
void			__exit__(char **__s);
void			__export__(char **__s, t_env_list **__env);
void			__insert__(char *__s, t_env_list **__env);
void			__add__export(t_env_list **env__, t_env_list *new__);
void			__unset__(char **__s, t_env_list **__env);
void			ft_print_tree(t_tree *tree, t_env_list **env);
void			__pipe__(t_tree *tree, t_env_list **env_list);
char			*ft_strjoin_equal(char const *s1, char const *s2);
char			**env_path(t_env_list *__env__);
void			__redir__(t_redir_node *__r, t_env_list **env);
int				__dir__(char **__s);
int				__accept__(char **__s);
char			*__access__(char **__s);
int				__cmp_char__(char s, char d);
void			__print_export__(t_env_list *__env, char i);
void			__sort_export__(t_env_list **__env);
int				__equal__(char *__s);
int				___check_kara__(char *__c);
char			*__val(char *env__, int i__);
char			*__key(char *env__, int i__);
int				__find_index(char *__s, char __f);
void			__right__(int __fd[2], t_tree *tree, t_env_list **env_list);
void			__left__(int __fd[2], t_tree *tree, t_env_list **env_list);
int				___isdigit(char *__c);
int				isalpha_or_(int c);
int				__check__(char *__s);
int				__check_2__(char *__s);
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
void			__print_tree(t_parser *parser, int io[2], t_tokens **token);
int				herdoc(t_parser	*parser);
void			ft_add_env_entrace(t_env_list **env, t_env_list *env_node);
t_env_list		*ft_create_env_node(char *key, char *value);
void			*ft_collect_tmp_mem(void *ptr);
void			__signal__main(void);
void			__history_main(char *cmd);
t_tree			*ft_parse_cmd(t_parser *parser);
void			ft_is_merged(t_tokens **tmp,
					int merged, char **str, t_tokens *current);
t_tokens		*__norm_ft_merge_init(t_tokens *tmp);
void			inside_merge(t_tokens *tmp, char **str, t_tokens *current);
void			norm_tmp(char **tmp);
void			__sigint2__(int __s);
char			**__norm_ft_mod_split_arg(char *cmd, char *arg);
char			**__norm_ft_mod_split_no_arg(char *cmd);
void			__error_norm(char *cmd);
int				__error__(char **__s, t_env_list *__env);
int				__exec__v1(char **__s, t_env_list *__env);
int				__exec__v2(char **__s, t_env_list *__env);
#endif
