# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/25 19:32:57 by adeburea          #+#    #+#              #
#    Updated: 2021/02/14 13:47:44 by adeburea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME	=	cub3D
CC		=	clang
FLAGS	=	-Wall -Werror -Wextra
INC		=	incs
OBJ		=	objs
SRC		=	srcs
LIBFT	=	libft
LIBMLX	=	libmlx
INCS	=	$(addprefix $(INC)/, cube3d.h)
OBJS	=	$(addprefix $(OBJ)/, $(SRCS:.c=.o))
SRCS 	=	get_next_line.c \
			parse_file.c \
			parse_map.c \
			motor.c

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	make -C $(LIBFT)
	make -C $(LIBMLX)
	$(CC) $(FLAGS) -I$(INC) -o $(NAME) srcs/main.c $(OBJS) -Llibft -lft -Llibmlx -lmlx -lX11 -lbsd -lm -lXext

$(OBJ)/%.o: $(SRC)/%.c $(INCS)
	$(CC) $(FLAGS) -I$(INC) -c $< -o $@

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT) clean
	make -C $(LIBMLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re: fclean all
