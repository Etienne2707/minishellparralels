# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 16:27:42 by mle-duc           #+#    #+#              #
#    Updated: 2023/10/25 19:39:47 by mle-duc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libft.a

CC =		cc

RM =		rm -f

CFLAGS =	-Werror -Wextra -Wall

SRCS =			ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strcmp.c \
				ft_strncmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				$(addprefix ft_printf/, \
				ft_print_char.c \
				ft_printf.c \
				ft_printf_utils.c \
				ft_print_hexa.c \
				ft_print_nb.c \
				ft_print_percent.c \
				ft_print_ptr.c \
				ft_print_str.c \
				ft_print_unsigned.c) \
				$(addprefix get_next_line/, \
				get_next_line.c \
				get_next_line_utils.c \
				)

SRCSBONUS =		ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c

OBJS =		${SRCS:.c=.o}

OBJSBONUS =	${SRCSBONUS:.c=.o}

all: $(NAME)

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	@ar -rcs $(NAME) ${OBJS}

bonus: ${OBJS} ${OBJSBONUS}
	ar -rcs $(NAME) ${OBJS} ${OBJSBONUS}

clean:
	${RM} ${OBJS} ${OBJSBONUS}

fclean: clean
	${RM} $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
