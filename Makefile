# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/25 19:32:57 by adeburea          #+#    #+#              #
#    Updated: 2021/02/14 02:09:34 by adeburea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME		=	cub3D
PATH_INC	=	incs
PATH_SRC	=	srcs
PATH_OBJ	=	objs
PATH_LIBFT	=	libft
PATH_LIBMLX	=	libmlx

SRCS =	get_next_line.c \
		parse_file.c \
		parse_map.c \
		motor.c
OBJS		=	$(addprefix $(PATH_OBJ)/, $(SRCS:.c=.o))
INCS		=	$(addprefix $(PATH_INC)/, cube3d.h)

CC		=	clang
FLAGS	=	-Wall -Werror -Wextra
COMP_ADD	=	-I$(PATH_INC)

all:	init $(NAME)

init:
	$(shell mkdir -p $(PATH_OBJ))
	make -C $(PATH_LIBFT)
	make -C $(PATH_LIBMLX)

$(NAME): $(OBJS) $(INCS)
	$(CC) $(FLAGS) $(COMP_ADD) -o $(NAME) srcs/main.c $(OBJS) -Llibft -lft -Llibmlx -lmlx -lX11 -lbsd -lm -lXext

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c $(INCS)
	$(CC) $(FLAGS) $(COMP_ADD) -c $< -o $@

clean:
	rm -rf $(PATH_OBJ)
	make -C $(PATH_LIBFT) clean
	make -C $(PATH_LIBMLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(PATH_LIBFT) fclean

re: fclean all
