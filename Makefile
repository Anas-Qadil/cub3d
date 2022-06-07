# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 17:38:01 by aqadil            #+#    #+#              #
#    Updated: 2022/06/07 16:03:59 by aqadil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRC		= cub3d.c itoa.c draw.c tools.c read_textures.c handle_images.c init.c render.c handle_colors.c keyhooks.c \
			draw_Map2d.c \
			draw_floor_ceiling.c \
			handle_player.c \
			draw_3d.c \
			interception_checks.c \
			game_states.c \
			free_exit.c \
			textures_calculs.c \
			animated_sprite.c \
			draw_3d_v2.c \
			init_v2.c \
			init_v3.c \
			interception_v2.c

OBJ		= cub3d.o itoa.o draw.o tools.o read_textures.o handle_images.o init.o render.o handle_colors.o keyhooks.o \
			draw_Map2d.o \
			draw_floor_ceiling.o \
			handle_player.o \
			draw_3d.o \
			interception_checks.o \
			game_states.o \
			free_exit.o \
			textures_calculs.o \
			animated_sprite.o \
			draw_3d_v2.o \
			init_v2.o \
			init_v3.o \
			interception_v2.o

CC 		= cc

MLX		= -lmlx -framework OpenGL -framework AppKit
HEADER = cub3d.h

$(NAME)	: $(OBJ) $(HEADER)
	$(CC) $(SRC) $(MLX) -o $(NAME)

%.o : %.c
	$(CC) $(MLX) -c $<

all	: $(NAME)


clean	: 
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all