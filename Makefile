# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 17:38:01 by aqadil            #+#    #+#              #
#    Updated: 2022/06/02 15:18:17 by aqadil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRC		= cub3d.c itoa.c draw.c tools.c read_textures.c handle_images.c init.c render.c handle_colors.c keyhooks.c
OBJ		= cub3d.o itoa.o draw.o tools.o read_textures.o handle_images.o init.o render.o handle_colors.o keyhooks.o

CC 		= cc

MLX		= -lmlx -framework OpenGL -framework AppKit
HEADER = cub3d.h

$(NAME)	: $(OBJ) $(HEADER)
	$(CC) $(SRC) $(MLX) -o $(NAME)

%.o:%.c
	$(CC) $(MLX) -c $<

all	: $(NAME)


clean	: 
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all