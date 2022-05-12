/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:14:32 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/11 11:14:42 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	sizef(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

static char	*fill_min_int(void)
{
	char	*str;

	str = malloc(12 * sizeof(char ));
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

static void	fill_the_array(char *str, int size, int sign, int n)
{
	while (--size != -1)
	{
		if (sign == 1 && size == 0)
			break ;
		str[size] = (n % 10) + 48;
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		size;

	sign = 0;
	if (n == -2147483648)
		return (fill_min_int());
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	size = sizef(n);
	str = (char *)malloc((size + 1 + sign) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (sign == 1)
	{
		str[0] = '-';
		size++;
	}
	fill_the_array(str, size, sign, n);
	str[size] = '\0';
	return (str);
}