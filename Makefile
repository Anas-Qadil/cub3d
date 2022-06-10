# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 17:38:01 by aqadil            #+#    #+#              #
#    Updated: 2022/06/10 20:44:22 by aqadil           ###   ########.fr        #
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
			interception_v2.c \
			render_v2.c \
			tools2.c \
			./parsing/parsing/checkingfile.c \
			./parsing/parsing/elements__.c \
			./parsing/parsing/parsing.c \
			./parsing/parsing/parsingmap.c \
			./parsing/parsing/parsingmap___.c \
			./parsing/parsing/elements.c \
			./parsing/parsing/elements___.c \
			./parsing/parsing/parsing_.c \
			./parsing/parsing/parsingmap_.c \
			./parsing/parsing/parsingmap____.c \
			./parsing/parsing/elements_.c \
			./parsing/parsing/elements____.c \
			./parsing/parsing/parsing__.c \
			./parsing/parsing/parsingmap__.c \
			./parsing/parsing/parsingmap_____.c \
			./parsing/get_next_line/get_next_line.c \
			./parsing/get_next_line/get_next_line_utils.c

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
			interception_v2.o \
			render_v2.o \
			tools2.o \
			./parsing/parsing/checkingfile.o \
			./parsing/parsing/elements__.o \
			./parsing/parsing/parsing.o \
			./parsing/parsing/parsingmap.o \
			./parsing/parsing/parsingmap___.o \
			./parsing/parsing/elements.o \
			./parsing/parsing/elements___.o \
			./parsing/parsing/parsing_.o \
			./parsing/parsing/parsingmap_.o \
			./parsing/parsing/parsingmap____.o \
			./parsing/parsing/elements_.o \
			./parsing/parsing/elements____.o \
			./parsing/parsing/parsing__.o \
			./parsing/parsing/parsingmap__.o \
			./parsing/parsing/parsingmap_____.o \
			./parsing/get_next_line/get_next_line.o \
			./parsing/get_next_line/get_next_line_utils.o

CC 		= cc

# MLX		= libmlx.dylib
MLX		= -lmlx -framework OpenGL -framework AppKit -g
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