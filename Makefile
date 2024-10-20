# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 18:53:41 by yboumanz          #+#    #+#              #
#    Updated: 2024/10/18 08:24:23 by yboumanz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex.c utils.c path.c process.c dup.c errors.c
OBJS = $(SRCS:.c=.o)

LIBDIR = libft
LIB = $(LIBDIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@$(MAKE) -s -C $(LIBDIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re
