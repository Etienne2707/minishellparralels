# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 16:55:24 by mle-duc           #+#    #+#              #
#    Updated: 2023/11/24 12:03:50 by mle-duc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell

CC =			cc

RM =			rm -f

INC_DIR =		./includes

LIBFT_DIR =		./libft

SRCS =			$(addprefix src/, \
				$(addprefix builtins/, env.c exit.c pwd.c echo.c export.c export_utils.c export_utils2.c unset.c cd.c cd_utils.c wd.c array_utils.c array_utils2.c) \
				$(addprefix exec/, executor.c exe2.c exec_utils.c pars.c heredoc.c child.c path.c) \
				$(addprefix utils/, utils.c utils2.c utils3.c) \
				$(addprefix parsing/, dollars.c dollars2.c dollars3.c list.c quote.c redirection.c redirection_utils.c split.c syntax_error.c syntax_error2.c syntax_utils.c token.c) \
				free.c \
				signal.c \
				main.c)

OBJS =			${SRCS:.c=.o}

CFLAGS =		-g3 #-Wall -Werror -Wextra

LIBFT_PATH =	libft/libft.a

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -I $(INC_DIR) -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	make -C libft
	@$(CC) $(OBJS) ${CFLAGS} -L$(LIBFT_DIR) -lft -o $(NAME) -lreadline

clean:
	${RM} ${OBJS}
	make clean -C libft

fclean: clean
	${RM} ${NAME}
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
