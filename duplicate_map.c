/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastano <rcastano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:59:42 by rcastano          #+#    #+#             */
/*   Updated: 2024/01/23 15:32:48 by rcastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

void	duplicate_map(t_data_global data)
{
	int		y;
	int		x;
	char	**duplicate;

	x = 0;
	y = 0;
	while (data.map[y] != NULL)
	{
		while (data.map[y][x] != '\0')
			x++;
		y++;
		x = 0;
	}
	duplicate = malloc(sizeof(char *) * (y + 1));
	if (!duplicate)
		return (0);
	duplicate[y] = NULL;
	while (y != 0)
	{
		y--;
		duplicate[y] = ft_strdup(data.map[y]);
	}
	return (duplicate);
}