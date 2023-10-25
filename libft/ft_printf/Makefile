# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 16:39:13 by mle-duc           #+#    #+#              #
#    Updated: 2023/04/09 02:49:26 by mle-duc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libftprintf.a

CC =		cc

RM =		rm -f

SRCS =		ft_printf.c \
			ft_print_char.c \
			ft_print_hexa.c \
			ft_print_percent.c \
			ft_print_ptr.c \
			ft_print_str.c \
			ft_print_unsigned.c \
			ft_print_nb.c \
			ft_printf_utils.c

OBJS =		${SRCS:.c=.o}

CFLAGS =	-Werror -Wextra -Wall

LIBFT_PATH = ../libft.a

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS} libft
	ar -rcs ${NAME} ${OBJS}

libft:
	make -C libft
	cp ${LIBFT_PATH} ${NAME}

clean:
	${RM} ${OBJS} ${OBJSBONUS}
	make clean -C libft

fclean: clean
	${RM} ${NAME}
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re libft
