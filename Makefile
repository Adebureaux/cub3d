# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/25 19:32:57 by adeburea          #+#    #+#              #
#    Updated: 2021/02/09 00:10:34 by adeburea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = clang
NAME = cube3D
CFLAGS = -Wall -Wextra -Werror
SANITIZER = -g -fsanitize=address,undefined
LIBFT = ./libft/libft.a
INC = -I./incs
SRCS =			srcs/main.c \
				srcs/parsing/get_next_line.c \
				srcs/parsing/parse_file.c \
				srcs/parsing/parse_map.c
OBJS = 			${SRCS:.c=.o}

.c.o:
	${CC} -fPIC ${CFLAGS} -c ${INC} $< -o ${<:.c=.o}

${NAME}: ${LIBFT} ${OBJS}
	${CC} ${OBJS} ${INC} ${LIBFT} ${CFLAGS} -o ${NAME}

${LIBFT}:
	@make all -C libft

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	@make clean -C libft
	rm -f ${NAME}
	rm -f ${LIBFT}

re: fclean all
