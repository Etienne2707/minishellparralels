# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 16:55:24 by mle-duc           #+#    #+#              #
#    Updated: 2023/11/15 08:25:24 by mle-duc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell

CC =			cc

RM =			rm -f

INC_DIR =		./includes

LIBFT_DIR =		./libft

SRCS =			$(addprefix src/, \
				dollars.c \
				dollars2.c \
				free.c \
				ft_malloc.c \
				list.c \
				quote.c \
				redirection.c \
				redirection_utils.c \
				split.c \
				syntax_error.c \
				syntax_utils.c \
				token.c \
				utils.c \
				utils2.c \
				utils3.c \
				path.c \
				executor.c \
				exe2.c \
				pars.c \
				array_utils.c \
				env.c \
				exit.c \
				pwd.c \
				echo.c \
				export.c \
				export_utils.c \
				unset.c \
				cd.c \
				wd.c \
				main.c)

OBJS =			${SRCS:.c=.o}

CFLAGS =		-g3 -Wall -Werror -Wextra

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
