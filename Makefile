# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/25 19:32:57 by adeburea          #+#    #+#              #
#    Updated: 2021/02/20 00:46:58 by adeburea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME	=	cub3D
CC		=	clang
FLAGS	=	-O3 -Wall -Wextra -Werror -g -fsanitize=address
INC		=	incs
OBJ		=	objs
SRC		=	srcs
LIBFT	=	libft
LIBMLX	=	libmlx
INCS	=	$(addprefix $(INC)/, cub3d.h)
OBJS	=	$(addprefix $(OBJ)/, $(SRCS:.c=.o))
SRCS 	=	get_next_line.c \
			parse_file.c \
			parse_map.c \
			start_game.c \
			raycasting.c

all: init $(NAME)

init:
	mkdir -p $(OBJ)
	make -C $(LIBFT)
	make -C $(LIBMLX)

$(NAME): $(OBJS) $(INCS)
	$(CC) $(FLAGS) -I$(INC) -o $(NAME) srcs/main.c $(OBJS) -Llibft -lft -Llibmlx -lmlx -lX11 -lbsd -lm -lXext

$(OBJ)/%.o: $(SRC)/%.c $(INCS)
	$(CC) $(FLAGS) -I$(INC) -c $< -o $@

clean:
	rm -rf $(OBJ)
	make -C $(LIBFT) clean
	make -C $(LIBMLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re: fclean all
