/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:25 by roberto           #+#    #+#             */
/*   Updated: 2024/01/17 16:12:52 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"


void render_ray(t_data_global *data, t_ray ray, int color)
{
	t_vector2 index;

	index = ray.origin;
	while((index.y >= 0 && index.y <= HEIGHT) && (index.x >= 0 && index.x <= WIDTH))
	{
		mlx_pixel_put(data->mlx, data->win, index.x, index.y, color);
		index.x = index.x + ray.direction.x;
		index.y = index.y + ray.direction.y;
	}
}

void render_rectangle(t_data_global *data, t_vector2 coords, t_vector2 size, int color)
{
	t_vector2 limit;
	t_vector2  index;

	index = coords;
	limit.x = coords.x + size.x;
	limit.y = coords.y + size.y;

	while(coords.y < limit.y)
	{
		while (coords.x < limit.x)
		{
			mlx_pixel_put(data->mlx, data->win, coords.x, coords.y, color);
			coords.x++;
		}
		coords.x = index.x;
		coords.y++;
	}
}

void render_character(t_data_global data)
{
	t_ray tmp_ray;

	tmp_ray.origin.x = (data.character.position.x * 32) + 16;
	tmp_ray.origin.y = (data.character.position.y * 32) + 16;

	tmp_ray.direction = data.character.direction;


	//printf("%i %i origin %i %i direction", tmp_ray.origin.x, tmp_ray.origin.y, tmp_ray.direction.x, tmp_ray.direction.y);
	render_ray(&data, tmp_ray, 0xff5900ff);

	render_rectangle((&data), (t_vector2){((data.character.position.x * 32) + 8), ((data.character.position.y * 32) + 8)}, (t_vector2){16, 16}, 0xff5900ff);
}

void render_walls(t_data_global *data)
{
	t_vector2 coords;
	coords.x = 0;
	coords.y = 0;

	while(data->map[coords.y] != NULL)
	{
		while (data->map[coords.y][coords.x] != '\0')
		{
			if (data->map[coords.y][coords.x] == '0')
			{
				render_rectangle(data, (t_vector2){(coords.x * 32), (coords.y * 32)}, (t_vector2){32, 32}, 0xffffffff);
			}
			else if (data->map[coords.y][coords.x] == '1')
			{
				render_rectangle(data, (t_vector2){(coords.x * 32), (coords.y * 32)}, (t_vector2){32, 32}, 0x055ae3ff);
			}
			coords.x++;
		}
		coords.x = 0;
		coords.y++;
	}
}

int	render(t_data_global *data)
{
	//mlx_clear_window(data->mlx, data->win);
	render_walls(data);
	render_character(*data);
	//mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
