# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 17:38:01 by aqadil            #+#    #+#              #
#    Updated: 2022/06/11 19:49:41 by aqadil           ###   ########.fr        #
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
			parsing/parsing/checkingfile.c \
			parsing/parsing/elements__.c \
			parsing/parsing/parsing.c \
			parsing/parsing/parsingmap.c \
			parsing/parsing/parsingmap___.c \
			parsing/parsing/elements.c \
			parsing/parsing/elements___.c \
			parsing/parsing/parsing_.c \
			parsing/parsing/parsingmap_.c \
			parsing/parsing/parsingmap____.c \
			parsing/parsing/elements_.c \
			parsing/parsing/elements____.c \
			parsing/parsing/parsing__.c \
			parsing/parsing/parsingmap__.c \
			parsing/parsing/parsingmap_____.c \
			parsing/get_next_line/get_next_line.c \
			parsing/get_next_line/get_next_line_utils.c \
			tools3.c \
			free.c


FLAGS	= -Wextra -Wall -Werror

OBJ = $(addprefix obj/, $(SRC:.c=.o))

CC 		= cc

MLX		= -lmlx -framework OpenGL -framework AppKit
HEADER = cub3d.h

$(NAME)	: $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(SRC) $(MLX) -o $(NAME)

obj/%.o : %.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) -c -o $@ $<

all	: $(NAME)

clean	: 
	rm -rf $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all