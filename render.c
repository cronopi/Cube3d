/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastano <rcastano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:25 by roberto           #+#    #+#             */
/*   Updated: 2024/01/30 15:47:16 by rcastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

void pixel_to_img(t_data_global *data, t_vector2 coords, int color)
{
	int pixel_position;

	pixel_position = ((coords.y * WIDTH) + coords.x) * 4;
	int pixel_bits = 32;
	int line_bytes = WIDTH;
	int endian = 0;
	char *buffer = mlx_get_data_addr(data->img, &pixel_bits, &line_bytes, &endian);

	buffer[pixel_position + 3] = (color >> 24);
	buffer[pixel_position + 2] = (color >> 16) & 0xFF;
	buffer[pixel_position + 1] = (color >> 8) & 0xFF;
	buffer[pixel_position + 0] = (color) & 0xFF;

}

void render_ray(t_data_global *data, t_ray ray, int color)
{
	t_fvector2 index;
	t_vector2 index2;
	int square_plx = 64;

	index.x = ceil(ray.origin.x);
	index.y = ceil(ray.origin.y);
	while((index.y >= 0 && index.y <= HEIGHT && index.y < ray.origin.y + (square_plx -16)) && (index.x >= 0 && index.x <= WIDTH && index.x < ray.origin.x + (square_plx -16))) // && index.x < ray.origin.x + (square_plx -16)
	{
		index2.x = ceil(index.x);
		index2.y = ceil(index.y);
		pixel_to_img(data, index2, color);
		index.x = index.x + ray.direction.x;
		index.y = index.y + ray.direction.y;
		//si no encuentra un 0 en la pared aumenta square_plx 32
	}
}

void	render_camera(t_data_global *data, int color)
{
	t_ray tmp_ray;

	data->character.camera_angle = 60;
	tmp_ray.origin.x = (data->character.position.x * 32) + 16;
	tmp_ray.origin.y = (data->character.position.y * 32) + 16;
	tmp_ray.direction = data->character.direction;
	render_ray(data, tmp_ray, color);
	tmp_ray.direction = Rotate(tmp_ray.direction, (-data->character.camera_angle/ 2));
/* 	int i = 0;
 	while(i < WIDTH)
	{
		render_ray(data, tmp_ray, color);
		tmp_ray.direction = Rotate(tmp_ray.direction, (data->character.camera_angle / WIDTH));
		printf("valor de :%i\n", i);
		i++;
	} */
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
			pixel_to_img(data, coords, color);
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
			if (data->map[coords.y][coords.x] == '0' || data->map[coords.y][coords.x] == 'E')
			{
				render_rectangle(data, (t_vector2){(coords.x * 32), (coords.y * 32)}, (t_vector2){32, 32}, 0xDFEDDDff);
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
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);

	render_walls(data);
	render_character(*data);
	render_camera(data, 0xff9900ff);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
	return (0);
}
