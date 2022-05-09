# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 17:38:01 by aqadil            #+#    #+#              #
#    Updated: 2022/05/08 11:14:58 by aqadil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRC		= cub3d.c 
OBJ		= cub3d.o 

CC 		= cc

MLX		= -lmlx -framework OpenGL -framework AppKit

$(NAME)	: $(OBJ)
	$(CC) $(SRC) $(MLX) -o $(NAME)

%.o:%.c
	$(CC) $(MLX) -c $<

all	: $(NAME)


clean	: 
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all