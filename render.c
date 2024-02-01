/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:25 by roberto           #+#    #+#             */
/*   Updated: 2024/02/01 09:48:36 by roberto          ###   ########.fr       */
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
float ray_collision(t_data_global *data, t_ray ray)
{
	float lengh_ray;

	lengh_ray = 0;
	(void)data;
	(void)ray;
	//obtengo la distancia del punto de origen al personaje y a la pared
	printf("valor de inicio%f %f\n", ray.origin.x, ray.origin.y);
	//printf("valor de inicio%f %f\n", ray.direction.x, ray.direction.y);
	//mientras ray.direction.x sea entre 0 y 1 yo se que va hacia la derecha en el mapa
	//mientras ray.direction.y sea entre 0 y 1 yo se que va hacia abajo en el mapa
	ray.check.x = ray.origin.x + 16;
	if (ray.direction.x >= 0 && ray.direction.x <= 1)
	{
		ray.check = ray.origin.x + 32;

/* 		index.x = index.x + ray.direction.x;
		index.y = index.y + ray.direction.y; */
	}
	lengh_ray = 300;
	return (lengh_ray);
}

void render_ray(t_data_global *data, t_ray ray, int color, float lengh_ray)
{
	t_fvector2 index;
	t_vector2 index2;

	(void)lengh_ray;

	index.x = ceil(ray.origin.x);
	index.y = ceil(ray.origin.y);
	while((index.y >= 0 && index.y <= HEIGHT) && (index.x >= 0 && index.x <= WIDTH)
	&& ((pow(index.x - ceil(ray.origin.x), 2) + (pow(index.y - ceil(ray.origin.y), 2))) <= (lengh_ray * lengh_ray)))
	{
		index2.x = ceil(index.x);
		index2.y = ceil(index.y);
		pixel_to_img(data, index2, color);
		index.x = index.x + ray.direction.x;
		index.y = index.y + ray.direction.y;
	}
}

void	render_camera(t_data_global *data, int color)
{
	t_ray tmp_ray;
	float lengh_ray;

	data->character.camera_angle = 60;
	tmp_ray.origin.x = (data->character.position.x * 32) + 16;
	tmp_ray.origin.y = (data->character.position.y * 32) + 16;
	tmp_ray.direction = data->character.direction;
	lengh_ray = ray_collision(data, tmp_ray);
	render_ray(data, tmp_ray, color, lengh_ray);
	tmp_ray.direction = Rotate(tmp_ray.direction, (-data->character.camera_angle/ 2));
/* 	int i = 0;
 	while(i < WIDTH)
	{
		render_ray(data, tmp_ray, color, lengh_ray);
		tmp_ray.direction = Rotate(tmp_ray.direction, (data->character.camera_angle / WIDTH));
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

	while(coords.y < limit.y) //coords.y >= 0 && coords.y <= HEIGHT
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
