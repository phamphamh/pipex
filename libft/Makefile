# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 18:57:21 by yboumanz          #+#    #+#              #
#    Updated: 2024/09/16 17:33:03 by yboumanz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =	ft_atoi.c ft_lstadd_back.c ft_memchr.c ft_split.c ft_strncmp.c \
		ft_bzero.c ft_lstadd_front.c ft_memcmp.c ft_strchr.c ft_strnstr.c \
		ft_calloc.c ft_lstclear.c ft_memcpy.c ft_strdup.c ft_strrchr.c \
		ft_isalnum.c ft_lstdelone.c ft_memmove.c ft_striteri.c ft_strtrim.c \
		ft_isalpha.c ft_lstiter.c ft_memset.c ft_strjoin.c ft_substr.c \
		ft_isascii.c ft_lstlast.c ft_putchar_fd.c ft_strlcat.c ft_tolower.c \
		ft_isdigit.c ft_lstmap.c ft_putendl_fd.c ft_strlcpy.c ft_toupper.c \
		ft_isprint.c ft_lstnew.c ft_putnbr_fd.c ft_strlen.c \
		ft_itoa.c ft_lstsize.c ft_putstr_fd.c ft_strmapi.c get_next_line.c \
		get_next_line_utils.c ft_strcmp.c ft_print_adress.c ft_printf.c \
		ft_printf_tools.c ft_strncmp.c ft_free_all.c\

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
