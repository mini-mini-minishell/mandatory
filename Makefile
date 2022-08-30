NAME 		=	minishell

CC 			=	cc -g -fsanitize=address
# CFLAGS		= -g3 -fsanitize=address
# export LDFLAGS="-L/usr/local/opt/readline/lib" 실행파일 만들때
# export CPPFLAGS="-I/usr/local/opt/readline/include" 인클루드 목적파일 만들때
# -lreadline -I/usr/local/Cellar/readline/8.1.2/include -L/usr/local/Cellar/readline/8.1.2/lib
RL_LINK		=	-L/usr/local/opt/readline/lib -lreadline
RL_INCLUDE	=	-I/usr/local/opt/readline/include
# RL_LINK		=	-L/opt/homebrew/opt/readline/lib -lreadline
# RL_INCLUDE	=	-I/opt/homebrew/opt/readline/include

RM					=	rm -f
BUILTIN_FILE_DIR	=	./built_in/
SRC_DIR 			= 	./sources/

FILES 		=			execute_command.c\
						execute_nonbuiltin.c\
						execute_simple.c\
						exit.c \
						get_next_line_utils.c \
						get_next_line.c \
						goto_func1.c \
						goto_func2.c \
						goto_func3.c \
						goto_state.c \
						heredoc.c \
						init_all.c \
						lex_func1.c \
						lex_func2.c \
						lex_func3.c \
						lex_func4.c \
						list_envp.c \
						list_envp2.c \
						list_stack.c \
						list_stack2.c \
						list_token.c \
						list_trans.c \
						list.c \
						list2.c \
						main.c \
						make_redir.c \
						parser.c \
						parsing.c \
						process_line.c \
						readline.c \
						reduce_func1.c \
						reduce_func2.c \
						reduce_func3.c \
						reduce_func4.c \
						reduce_utils.c \
						run_lexer.c \
						run_parser.c \
						signal_hadler.c\
						test.c \
						utils_fd.c \
						utils_split.c \
						utils_string.c

BUILTIN_FILE		=	ft_cd_utils.c\
						ft_cd_utils2.c\
						ft_cd.c\
						ft_echo.c \
						ft_env.c \
						ft_exit.c \
						ft_export_envp.c \
						ft_export_utils.c \
						ft_export.c \
						ft_unset.c \
						ft_pwd.c \
						ft_unset.c

SRCS		=	$(addprefix $(SRC_DIR), $(FILES)) \
				$(addprefix $(BUILTIN_FILE_DIR), $(BUILTIN_FILE))

OBJS		=	$(SRCS:%.c=%.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(RL_INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(RL_LINK) -o $@ $^

debug: ${SRCS}
	gcc -g3 -fsanitize=address ${SRCS} -o main

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	make fclean
	make all
