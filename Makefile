# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 17:38:01 by aqadil            #+#    #+#              #
#    Updated: 2022/02/14 17:41:16 by aqadil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRC		= cub3d.c
OBJ		= cub3d.o

$(NAME)	: $(OBJ)
	cc $(OBJ) -o $(NAME)


all	: $(NAME)

%.o:%.c
	cc -o $@ -c $<

clean	: 
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all