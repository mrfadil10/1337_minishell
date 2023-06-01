# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 15:15:14 by stemsama          #+#    #+#              #
#    Updated: 2023/05/25 17:32:26 by mfadil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT			=	./libft/libft.a
CC = cc
FLAGS = -Wall -Werror -Wextra -I/Users/mfadil/.brew/opt/readline/include -g
VAR = -lreadline -L/Users/mfadil/.brew/opt/readline/lib -lhistory

SRC = tools1.c tools2.c main.c \
		implement_cd.c implement_echo.c implement_env.c implement_exit.c\
		implement_unset.c implement_pwd.c implement_export.c\
		handler_signals.c \
		parsing.c


OBJECT = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECT) minishell.h
	@make -C ./libft all bonus
	$(CC) $(FLAGS) $(LIBFT) $(OBJECT) -o $(NAME) $(VAR) -g

%.o:%.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	@make -C ./libft clean
	rm -f $(OBJECT)

fclean : clean
	@make -C ./libft fclean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean re all libft
