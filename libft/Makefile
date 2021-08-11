# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: motoure <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 02:25:18 by motoure           #+#    #+#              #
#    Updated: 2021/07/02 02:48:11 by motoure          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_isprint.c \
	  ft_itoa.c ft_calloc.c\
	  ft_memccpy.c ft_memchr.c ft_memcpy.c ft_memcmp.c\
	  ft_memmove.c ft_memset.c ft_putchar_fd.c \
	  ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_putstr_fd.c ft_split.c ft_strchr.c\
	  ft_strdup.c ft_strrev.c\
	  ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	  ft_strmapi.c ft_strncmp.c\
	  ft_strnstr.c ft_strrchr.c \
	  ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	  ft_putchar_str.c ft_memsub.c ft_realloc.c ft_strndup.c\

OBJ = $(subst .c,.o,$(SRC))

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

OBJ : $(subst .o,.c,$(SRC))
	gcc -c $(CFLAGS) $(SRC)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

main : main.c libft.a
	gcc -Wall -Wextra -Werror main.c libft.a

.PHONY: clean fclean all re
