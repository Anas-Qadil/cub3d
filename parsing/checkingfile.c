/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkingfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:40:28 by sakllam           #+#    #+#             */
/*   Updated: 2022/05/08 18:11:41 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	checkfilename(char *name)
{
	int	i;

	i = 0;
	while (name[i])
		i++;
	if (i > 4 && name[i - 1] == 'b' && name[i - 2] == 'u'
		&& name[i - 3] == 'c' && name[i - 4] == '.')
		return ;
	printf ("check extantion in file name\n");
	exit (0);
}

int	accessingallowed(char *name)
{
	int	fd;
	checkfilename(name);
	fd = open (name, O_RDONLY);
	if (fd >= 0)
		return (fd);
	perror("cube3d: ");
	exit (0);
}
