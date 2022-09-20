# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 20:23:14 by hogkim            #+#    #+#              #
#    Updated: 2022/09/20 10:53:09 by hogkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				=	minishell

CC 					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g3

# RL_LINK				=	-L/Users/hogkim/.brew/opt/readline/lib -lreadline
# RL_INCLUDE			=	-I/Users/hogkim/.brew/opt/readline/include
RL_LINK				=	-L/opt/homebrew/opt/readline/lib -lreadline
RL_INCLUDE			=	-I/opt/homebrew/opt/readline/include

RM					=	rm -f
BUILTIN_FILE_DIR	=	./built_in/
EXECUTE_FILE_DIR	=	./execute/
EXPANSION_FILE_DIR	=	./expansion/
SRC_DIR 			= 	./sources/

FILES 					=	exit.c \
							free.c \
							get_next_line_utils.c \
							get_next_line.c \
							goto_func1.c \
							goto_func2.c \
							goto_func3.c \
							goto_state.c \
							heredoc.c \
							heredoc_utils.c \
							init_all.c \
							lex_func1.c \
							lex_func2.c \
							lex_func3.c \
							lex_func4.c \
							list_envp.c \
							list_envp2.c \
							list_heredoc.c \
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
							reduce_make.c \
							reduce_utils.c \
							run_lexer.c \
							run_parser.c \
							signal_hadler.c\
							utils_fd.c \
							utils_itoa.c \
							utils_split.c \
							utils_string.c \
							utils_string2.c \
							utils_string3.c

BUILTIN_FILE			=	ft_cd_utils.c\
							ft_cd.c\
							ft_echo.c \
							ft_env.c \
							ft_exit_utils.c \
							ft_exit.c \
							ft_export_envp.c \
							ft_export_utils.c \
							ft_export.c \
							ft_unset.c \
							ft_pwd.c \
							ft_unset.c

EXCUTE_FILE				=	execute_builtin.c \
							execute_command.c \
							execute_connect.c\
							execute_do_redirection.c \
							execute_get_redir_fd.c \
							execute_nonbuiltin_utils1.c \
							execute_nonbuiltin.c \
							execute_pipe.c\
							execute_simple.c \
							execute_subshell.c \
							execute_utils.c \

EXPANSION_FILE			=	expand_no_variable.c \
							expand_nosplit.c \
							expand_string.c \
							expand_substitute.c \
							expand_variable.c \
							expansion_filename.c \
							expansion_match.c \
							expansion_one_node.c \
							expansion_word_list.c \
							expansion.c \

SRCS					=	$(addprefix $(SRC_DIR), $(FILES)) \
							$(addprefix $(BUILTIN_FILE_DIR), $(BUILTIN_FILE)) \
							$(addprefix $(EXECUTE_FILE_DIR), $(EXCUTE_FILE)) \
							$(addprefix $(EXPANSION_FILE_DIR), $(EXPANSION_FILE))

BUILTIN_FILE_DIR_B		=	./built_in_bonus/
EXECUTE_FILE_DIR_B		=	./execute_bonus/
EXPANSION_FILE_DIR_B	=	./expansion_bonus/
SRC_DIR_B 				= 	./sources_bonus/

FILES_B					=	exit_bonus.c \
							get_next_line_utils_bonus.c \
							get_next_line_bonus.c \
							goto_func1_bonus.c \
							goto_func2_bonus.c \
							goto_func3_bonus.c \
							goto_state_bonus.c \
							heredoc_bonus.c \
							heredoc_utils_bonus.c \
							init_all_bonus.c \
							lex_func1_bonus.c \
							lex_func2_bonus.c \
							lex_func3_bonus.c \
							lex_func4_bonus.c \
							list_envp_bonus.c \
							list_envp2_bonus.c \
							list_heredoc_bonus.c \
							list_stack_bonus.c \
							list_stack2_bonus.c \
							list_token_bonus.c \
							list_trans_bonus.c \
							list_bonus.c \
							list2_bonus.c \
							main_bonus.c \
							make_redir_bonus.c \
							parser_bonus.c \
							parsing_bonus.c \
							process_line_bonus.c \
							readline_bonus.c \
							reduce_func1_bonus.c \
							reduce_func2_bonus.c \
							reduce_func3_bonus.c \
							reduce_func4_bonus.c \
							reduce_make_bonus.c \
							reduce_utils_bonus.c \
							run_lexer_bonus.c \
							run_parser_bonus.c \
							signal_hadler_bonus.c\
							utils_fd_bonus.c \
							utils_itoa_bonus.c \
							utils_split_bonus.c \
							utils_string_bonus.c \
							utils_string2_bonus.c \
							utils_string3_bonus.c

BUILTIN_FILE_B			=	ft_cd_utils_bonus.c\
							ft_cd_bonus.c\
							ft_echo_bonus.c \
							ft_env_bonus.c \
							ft_exit_utils_bonus.c \
							ft_exit_bonus.c \
							ft_export_envp_bonus.c \
							ft_export_utils_bonus.c \
							ft_export_bonus.c \
							ft_unset_bonus.c \
							ft_pwd_bonus.c \
							ft_unset_bonus.c

EXCUTE_FILE_B			=	execute_builtin_bonus.c \
							execute_command_bonus.c \
							execute_connect_bonus.c\
							execute_do_redirection_bonus.c \
							execute_get_redir_fd_bonus.c \
							execute_nonbuiltin_utils1_bonus.c \
							execute_nonbuiltin_bonus.c \
							execute_pipe_bonus.c\
							execute_simple_bonus.c \
							execute_subshell_bonus.c \
							execute_utils_bonus.c \

EXPANSION_FILE_B		=	expand_no_variable_bonus.c \
							expand_nosplit_bonus.c \
							expand_string_bonus.c \
							expand_substitute_bonus.c \
							expand_variable_bonus.c \
							expansion_filename_bonus.c \
							expansion_match_bonus.c \
							expansion_one_node_bonus.c \
							expansion_word_list_bonus.c \
							expansion_bonus.c \

BSRC_DIR				=	minishell_bonus/
BSRC					=	$(addprefix $(SRC_DIR_B), $(FILES_B)) \
							$(addprefix $(BUILTIN_FILE_DIR_B), $(BUILTIN_FILE_B)) \
							$(addprefix $(EXECUTE_FILE_DIR_B), $(EXCUTE_FILE_B)) \
							$(addprefix $(EXPANSION_FILE_DIR_B), $(EXPANSION_FILE_B))
OBJS					=	$(SRCS:%.c=%.o)
BOBJ					=	$(BSRC:.c=.o)

ifeq ($(MAKECMDGOALS),bonus)
OBJS					=		$(BOBJ)
endif

.PHONY: all clean fclean re

all: $(NAME)

bonus : all

%.o: %.c
	$(CC) $(CFLAGS) $(RL_INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(RL_LINK) -o $@ $^

clean:
	$(RM) $(OBJS) $(BOBJ)

fclean: clean
	$(RM) $(NAME)

re:
	make fclean
	make all
