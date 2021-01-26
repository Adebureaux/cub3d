.PHONY: all clean fclean re

CC = gcc
NAME = cube3d
CFLAGS = -Wall -Wextra -Werror
SANITIZER = -g -fsanitize=address,undefined
LIBFT = libft/libft.a
INC = -I./incs
SRCS =			srcs/main.c \
				srcs/parsing/get_next_line.c \
				srcs/utilities/string.c
OBJS = 			${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c ${INC} $< -o ${<:.c=.o}

${NAME}: ${LIBFT} ${OBJS}
	${CC} ${SANITIZER} ${INC} ${LIBFT} ${CFLAGS} ${OBJS} -o ${NAME}
	rm -rf cube3d.dSYM

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
