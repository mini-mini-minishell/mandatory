NAME 		=	minishell

CC 			=	cc
CFLAGS		=	-g -Wall -Werror -Wextra
# RL_LINK	=	-lreadline -L/usr/local/opt/readline/lib
# RL_INCLUDE	=	-I/usr/local/opt/readline/include
# # RL_LINK		=	-L/opt/homebrew/opt/readline/lib -lreadline
# # RL_INCLUDE	=	-I/opt/homebrew/opt/readline/include
RM			=	rm -f
SRC_DIR 	= 	./sources/

FILES 		=	exit.c \
				heredoc.c \
				init_all.c \
				lex_func1.c \
				lex_func2.c \
				lex_func3.c \
				lex_func4.c \
				list_envp.c \
				list_envp2.c \
				list_stack.c \
				list_token.c \
				list.c \
				main.c \
				make_redir.c \
				parsing.c \
				process_line.c \
				readline.c \
				reduce_func1.c \
				reduce_func2.c \
				reduce_func3.c \
				reduce_func4.c \
				run_lexer.c \
				test.c \
				utils_reduce.c \
				utils_split.c \
				utils_string.c

SRCS		=	$(addprefix $(SRC_DIR), $(FILES))
OBJS		=	$(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(RL_LINK) -o $@ $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	make fclean
	make all
