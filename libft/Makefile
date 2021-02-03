# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/05 23:54:27 by adeburea          #+#    #+#              #
#    Updated: 2021/02/03 13:49:36 by adeburea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re bonus

CC = gcc
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
SRCS =			ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memccpy.c \
				ft_memmove.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strlen.c \
				ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strcmp.c \
				ft_strncmp.c \
				ft_strcpy.c \
				ft_strncpy.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_realloc.c \
				ft_strdup.c \
				ft_strndup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_nbrlen_base.c \
				ft_putnbr_base.c
BONUS_SRCS =	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c
OBJS = 			${SRCS:.c=.o}
BONUS_OBJS =	${BONUS_SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}
	ranlib ${NAME}

all: ${NAME} bonus

bonus: ${BONUS_OBJS}
	ar rc ${NAME} ${BONUS_OBJS}
	ranlib ${NAME}

clean:
	rm -f ${OBJS}
	rm -f ${BONUS_OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
