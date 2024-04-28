/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:12:24 by roberto           #+#    #+#             */
/*   Updated: 2024/04/18 11:05:13 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

void	free_leaks(t_data_global *data)
{
	(void)data;
	ft_putstr_fd("Error de algun tipo\n", 1);
/* 	free_map(data.dup_map);
	free_map(data.map); */
	//mlx_destroy_display(data->mlx);
	//free(data->mlx);
	exit(1);
}

void	check_walls_floodfill2(t_data_global *data)
{
	t_vector2	coords;

	coords.x = 0;
	coords.y = 0;
	while (data->dup_map[coords.y][coords.x] != '\0')
	{
		if (data->dup_map[coords.y][coords.x] == 'v')
		{
			printf("Error de algun tipo check_wall_floodfill2\n");
			free_leaks(data);
		}
		coords.x++;
	}
}

void	check_walls_floodfill(t_data_global *data)
{
	t_vector2	coords;

	coords.x = 0;
	coords.y = 0;
	printf("dup: %s", data->dup_map[coords.y]);
	while (data->dup_map[coords.y] != NULL)
	{
		if (data->dup_map[coords.y][coords.x] == 'v')
			{
			printf("Error de algun tipo check_wall_flood\n");
			free_leaks(data);
		}
		coords.y++;
	}
	coords.y = coords.y - 1;
	while (data->dup_map[coords.y][coords.x] != '\0')
	{
		if (data->dup_map[coords.y][coords.x] == 'v')
		{
			printf("Error de algun tipo ch\n");
			free_leaks(data);
		}
		coords.x++;
	}
	coords.x = coords.x - 1;
	while (coords.y >= 0)
	{
		if (data->dup_map[coords.y][coords.x] == 'v')
		{
			printf("Error de algun tipo check\n");
			free_leaks(data);
		}
		coords.y--;
	}
	check_walls_floodfill2(data);
}

void	floodfill_duplicate(char **duplicate, int x, int y)
{
	duplicate[y][x] = 'v';
	if (y > 0 && duplicate[y - 1][x] != '1' && duplicate[y - 1][x] != 'v')
		floodfill_duplicate(duplicate, x, y - 1);
	if (duplicate[y][x + 1] != '\0'
		&& duplicate[y][x + 1] != '1' && duplicate[y][x + 1] != 'v')
		floodfill_duplicate(duplicate, x + 1, y);
	if (duplicate[y + 1] != NULL
		&& duplicate[y + 1][x] != '1' && duplicate[y + 1][x] != 'v')
		floodfill_duplicate(duplicate, x, y + 1);
	if (x > 0 && duplicate[y][x - 1] != '1' && duplicate[y][x - 1] != 'v')
		floodfill_duplicate(duplicate, x - 1, y);
	if (y > 0 && x > 0 && duplicate[y - 1][x - 1] != '1'
		&& duplicate[y - 1][x - 1] != 'v')
		floodfill_duplicate(duplicate, x - 1, y - 1);
	if (y > 0 && duplicate[y - 1][x + 1] != '\0'
		&& duplicate[y - 1][x + 1] != '1' && duplicate[y - 1][x + 1] != 'v')
		floodfill_duplicate(duplicate, x + 1, y - 1);
	if (x > 0 && duplicate[y + 1] != NULL && duplicate[y + 1][x - 1] != '1'
		&& duplicate[y + 1][x - 1] != 'v')
		floodfill_duplicate(duplicate, x - 1, y + 1);
	if (duplicate[y + 1] != NULL && duplicate[y + 1][x + 1] != '\0'
		&& duplicate[y + 1][x + 1] != '1' && duplicate[y + 1][x + 1] != 'v')
		floodfill_duplicate(duplicate, x + 1, y + 1);
}

void	floodfill(char **duplicate, int x, int y)
{
	duplicate[y][x] = 'x';
	if (y > 0 && duplicate[y - 1][x] != '1' && duplicate[y - 1][x] != 'x')
		floodfill(duplicate, x, y - 1);
	if (duplicate[y][x + 1] != '\0'
		&& duplicate[y][x + 1] != '1' && duplicate[y][x + 1] != 'x')
		floodfill(duplicate, x + 1, y);
	if (duplicate[y + 1] != NULL
		&& duplicate[y + 1][x] != '1' && duplicate[y + 1][x] != 'x')
		floodfill(duplicate, x, y + 1);
	if (x > 0 && duplicate[y][x - 1] != '1' && duplicate[y][x - 1] != 'x')
		floodfill(duplicate, x - 1, y);
}
