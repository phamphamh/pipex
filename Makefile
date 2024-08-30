# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 18:53:41 by yboumanz          #+#    #+#              #
#    Updated: 2024/08/30 18:53:51 by yboumanz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS =	

OBJS = $(SRCS:.c=.o)

LIBDIR = libft
LIB = $(LIBDIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

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
