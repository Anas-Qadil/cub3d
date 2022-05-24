/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:37:11 by sakllam           #+#    #+#             */
/*   Updated: 2022/05/09 18:13:43 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	parsing(char *argv)
{
	int			fd;
	t_mapelm	*map;

	fd = accessingallowed(argv[1]);
	close (fd);
	map = parsingmap(argv[1]);
}