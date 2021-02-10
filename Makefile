# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/25 19:32:57 by adeburea          #+#    #+#              #
#    Updated: 2021/02/10 15:40:31 by adeburea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = clang
NAME = cube3D
LCUBE = cube3D.a
CFLAGS = -Wall -Wextra -Werror
SANITIZER = -g -fsanitize=address,undefined
LIBFT = ./libft/libft.a
MLX = ./mlx_linux
INC = -I./incs
SRCS =	srcs/parsing/get_next_line.c \
		srcs/parsing/parse_file.c \
		srcs/parsing/parse_map.c
OBJS = ${SRCS:.c=.o}

MINI_OBJS =	minilibx/mlx_clear_window.o \
			minilibx/mlx_destroy_image.o \
			minilibx/mlx_destroy_window.o  \
			minilibx/mlx_expose_hook.o  \
			minilibx/mlx_flush_event.o  \
			minilibx/mlx_get_color_value.o \
			minilibx/mlx_get_data_addr.o  \
			minilibx/mlx_hook.o \
			minilibx/mlx_init.o  \
			minilibx/mlx_int_anti_resize_win.o \
			minilibx/mlx_int_do_nothing.o  \
			minilibx/mlx_int_get_visual.o \
			minilibx/mlx_int_param_event.o \
			minilibx/mlx_int_set_win_event_mask.o \
			minilibx/mlx_int_str_to_wordtab.o \
			minilibx/mlx_int_wait_first_expose.o \
			minilibx/mlx_key_hook.o \
			minilibx/mlx_loop.o  \
			minilibx/mlx_loop_hook.o \
			minilibx/mlx_mouse_hook.o \
			minilibx/mlx_new_image.o \
			minilibx/mlx_new_window.o \
			minilibx/mlx_pixel_put.o \
			minilibx/mlx_put_image_to_window.o \
			minilibx/mlx_rgb.o \
			minilibx/mlx_string_put.o \
			minilibx/mlx_xpm.o

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
		@make -C ${MLX}
		@make all -C libft
		@cp ${LIBFT} ./${LCUB}
		ar rc ${LCUB} ${OBJS}
		/bin/rm -f ${LIBFT}
		ranlib ${LIBCUB}
		${CC} -o ${NAME} main.c ${MINI_OBJS} ${LCUB} -I${INC} -lm  -lXext -lX11 -lbsd


all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	@make clean -C libft
	rm -f ${NAME}
	rm -f ${LIBFT}

re: fclean all
