LIBFT = ./libft/libft.a
SRC = minishell.c env.c gc.c debug_env.c tokenizer.c debug_tokenizer.c tokenizer_manager.c tokenizer_manager_extension1.c \
		merger.c syntax_analyser.c tokenizer_norm.c tokenizer_utils.c expander.c expander_utils.c \
		__exec.c __status.c __signal.c __builtin.c __echo.c __pwd.c __cd.c __env.c __exit.c __export.c __unset.c \
		__pipe.c  __u_export.c __utils.c __find.c exec_redir.c __utils1.c __utils2.c norminette.c __run.c merger_norm.c __tmp.c __exec_norm.c __execv.c
INCLUDE = ./minishell.h libft/libft.h
NAME = minishell

OBJ = $(SRC:.c=.o)
CC = cc

CFLAGS = -c -I. -I/goinfre/$(shell whoami)/.brew/opt/readline/include -Wall -Wextra -Werror
LFALGS = -L/goinfre/$(shell whoami)/.brew/opt/readline/lib -lreadline

%.o : %.c $(INCLUDE)
	$(CC) -O2 $(CFLAGS) $<

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) -fsanitize=address $(LFALGS) $^ -o $(NAME)

$(LIBFT) :
	cd libft && $(MAKE)

clean :
	/bin/rm -rf $(OBJ) && cd libft && $(MAKE) clean

fclean : clean
	rm -rf $(NAME) && cd libft && $(MAKE) fclean

re : fclean $(NAME)
