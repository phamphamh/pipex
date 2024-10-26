# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 18:53:41 by yboumanz          #+#    #+#              #
#    Updated: 2024/10/26 23:27:00 by yboumanz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
BONUS_DIR = bonus

SRCS =	$(SRC_DIR)/pipex.c \
		$(SRC_DIR)/process.c \
		$(SRC_DIR)/errors.c \
		$(SRC_DIR)/dup.c \
		$(SRC_DIR)/path.c \
		$(SRC_DIR)/utils.c \

SRCS_BONUS =	$(BONUS_DIR)/pipex_bonus.c \
				$(BONUS_DIR)/process_bonus.c \
				$(BONUS_DIR)/errors_bonus.c \
				$(BONUS_DIR)/dup_bonus.c \
				$(BONUS_DIR)/path_bonus.c \
				$(BONUS_DIR)/utils_bonus.c \

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

INCLUDES = -I./include -I./$(LIBFT_DIR)
INCLUDES_BONUS = -I./include_bonus -I./$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(OBJS_BONUS)
	$(CC) $(OBJS_BONUS) -L$(LIBFT_DIR) -lft -o $(NAME_BONUS)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
