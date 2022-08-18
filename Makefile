NAME 		=	minishell

CC 			=	cc
CFLAGS		=	-g -Wall -Werror -Wextra
# RL_LINK	=	-lreadline -L/usr/local/opt/readline/lib
# RL_INCLUDE	=	-I/usr/local/opt/readline/include
# # RL_LINK		=	-L/opt/homebrew/opt/readline/lib -lreadline
# # RL_INCLUDE	=	-I/opt/homebrew/opt/readline/include
RM			=	rm -f
SRC_DIR 	= 	./sources/

FILES 		=	*.c

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
