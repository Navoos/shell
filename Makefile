LIBFT = ./libft/libft.a
SRC = minishell.c env.c gc.c debug_env.c tokenizer.c debug_tokenizer.c tokenizer_manager.c tokenizer_manager_extension1.c \
		merger.c syntax_analyser.c tokenizer_norm.c tokenizer_utils.c expander.c expander_utils.c \
		exec_redir.c __utils1.c __utils2.c norminette.c merger_norm.c \
		ft_exec_cd.c ft_exec_echo.c ft_exec_env_crud.c ft_exec_env_utils.c ft_exec_env.c ft_exec_main.c ft_exec_pwd.c ft_exec_shell.c ft_exec_utils.c ft_exec_pipe.c ft_exec_exit.c ft_exec_redir.c ft_exec_signals.c ft_exec_main_utils.c
INCLUDE = ./minishell.h libft/libft.h
NAME = minishell

OBJ = $(SRC:.c=.o)
CC = cc

CFLAGS = -c -I. -I/goinfre/$(shell whoami)/homebrew/opt/readline/include -Wall -Wextra -Werror
LFALGS = -L/goinfre/$(shell whoami)/homebrew/opt/readline/lib -lreadline

%.o : %.c $(INCLUDE)
	$(CC) -O2 -g $(CFLAGS) $<

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) -fsanitize=address -g $(LFALGS) $^ -o $(NAME)

$(LIBFT) :
	cd libft && $(MAKE)

clean :
	/bin/rm -rf $(OBJ) && cd libft && $(MAKE) clean

fclean : clean
	rm -rf $(NAME) && cd libft && $(MAKE) fclean

re : fclean $(NAME)
