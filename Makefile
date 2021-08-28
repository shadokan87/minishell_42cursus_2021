NAME	=	minishell

CC		=	gcc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -g

LFLAGS	=	-I. -lncurses -lreadline #-fsanitize=address

LIBFT	=	./libft/libft.a

SRCS	=	./srcs/main/main.c \
			./srcs/gc/garbage_co.c \
			./srcs/gc/garbage_co2.c \
			./srcs/gc/garbage_co3.c \
			./parsing/parsing_pass1/parsing_p.c \
			./parsing/parsing_pass1/parsing_p_par.c	\
			./parsing/parsing_pass1/parsing_p_quotes.c \
			./parsing/parsing_pass1/parsing_p_quotes_2.c \
			./parsing/parsing_pass1/parsing_p_symbol.c \
			./parsing/parsing_pass2/parsing_p_p_par.c \
			./parsing/string_utils.c \
			./parsing/string_utils_2.c \
			./parsing/string_utils_3.c \
			./parsing/string_utils_4.c \
			./parsing/string_utils_5.c \
			./init/init1.c \
			./parsing/parsing_pass2/parsing_p_p_token.c \
			./_IO/handle_redirection.c \
			./_IO/input.c \
			./_IO/output.c \
			./_IO/pipe/pipe.c \
			./_cmd_exec/[execve].c \
			./_cmd_exec/[execve2].c \
			./_cmd_exec/exec_type[pipe_no_pipe].c \
			./_cmd_exec/handle_args.c \
			./_cmd_exec/handle_cmd.c \
			./_cmd_exec/handle_cmd2.c \
			./_env/env1.c \
			./_builtins/builtin1.c \
			./_builtins/builtin1.5.c \
			./_builtins/builtin2.c \
			./_builtins/builtin3.c \
			./_builtins/ft_internal.c \
			./_builtins/random_utils1.c \
			./_wildcards/handle_wildcards.c \
			./_wildcards/match.c \
			./_wildcards/multiple.c \
			./_wildcards/single.c \
			./_wildcards/determine.c \
			./error/error.c

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			make -C libft
			${CC} ${CFLAGS} ${LFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

clean:
			$(RM) $(OBJS)
			make clean -C libft

fclean:		clean
			$(RM) $(NAME) $(LIBFT)

re:			fclean $(NAME)

f:			re
			./minishell

.PHONY:		all clean fclean re f
