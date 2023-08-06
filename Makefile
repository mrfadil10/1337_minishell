# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 15:15:14 by stemsama          #+#    #+#              #
#    Updated: 2023/08/06 20:07:12 by mfadil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT			=	./libft/libft.a
CC = cc
FLAGS = -Wall -Werror -Wextra -I/Users/mfadil/.brew/opt/readline/include -g #-fsanitize=address
VAR = -lreadline -L/Users/mfadil/.brew/opt/readline/lib -lhistory

SRC = main.c \
		tools/tools1.c tools/tools2.c tools/tools3.c tools/utils_1.c tools/utils_2.c\
		builtins/implement_cd.c builtins/implement_echo.c builtins/implement_env.c \
		builtins/implement_exit.c builtins/implement_unset.c builtins/implement_pwd.c \
		builtins/implement_export.c\
		parsing/expand_tools.c parsing/parsing_tools1.c parsing/parsing_tools2.c parsing/parsing_tools3.c parsing/parsing.c \
		handler_signals.c parsing/normalize.c parsing/normalize_tools.c parsing/expander.c parsing/herdc_exp.c

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
