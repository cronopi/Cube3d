/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:25 by roberto           #+#    #+#             */
/*   Updated: 2024/02/19 12:07:16 by roberto          ###   ########.fr       */
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
/* float ray_collision(t_data_global *data, t_ray ray)
{
	float lengh_ray;
	float lengh_ray_y;
	float h;
	float h2;
	t_vector2 map_position;
	t_fvector2 pixel_position;

	lengh_ray = 0;
	pixel_position.x = ray.origin.x + 16;
	pixel_position.y = ray.origin.y + 16;
	map_position.x = ray.origin.x / 32;
	map_position.y = ray.origin.y / 32;
	while (ray.direction.x > 0)
	{
		//printf("mirando derecha\n");
		if(data->map[map_position.y][map_position.x] == '1')
		{
			lengh_ray = pixel_position.x - ray.origin.x - 32;
			lengh_ray_y = (ray.direction.y * lengh_ray) / ray.direction.x;
			h2 = pow((lengh_ray), 2) + pow((lengh_ray_y), 2);
			break;
		}
		map_position.x += 1;
		pixel_position.x = pixel_position.x + 32;
		pixel_position.y = pixel_position.y + (32.0 * ray.direction.y / ray.direction.x);
	}
	while (ray.direction.x < 0)
	{
		//printf("mirando izquierda\n");
		if(data->map[map_position.y][map_position.x] == '1')
		{
			lengh_ray = ray.origin.x - pixel_position.x;
			lengh_ray_y = (ray.direction.y * lengh_ray) / ray.direction.x;
			h2 = pow((lengh_ray), 2) + pow((lengh_ray_y), 2);
			break;
		}
		map_position.x -= 1;
		pixel_position.x = pixel_position.x - 32;
		pixel_position.y = pixel_position.y + (32.0 * ray.direction.y / ray.direction.x);
	}
	map_position.x = ray.origin.x / 32;
	map_position.y = ray.origin.y / 32;
	while (ray.direction.y > 0)
	{
		//printf("mirando abajo\n");
		if(data->map[map_position.y][map_position.x] == '1')
		{
			lengh_ray_y = pixel_position.y - ray.origin.y -32;
			//printf("el pixel %f y el rayo %f\n", pixel_position.y, ray.origin.y);
			//lengh_ray_y = pixel_position.y - ray.origin.y;
			lengh_ray = (ray.direction.x * lengh_ray_y) / ray.direction.y;
			h = pow((lengh_ray), 2) + pow((lengh_ray_y), 2);
			break;
		}
		map_position.y += 1;
		pixel_position.y += 32;
		pixel_position.x = pixel_position.x + (32.0 * ray.direction.x / ray.direction.y);
	}
	while (ray.direction.y < 0)
	{
		//printf("mirando arriba\n");
		if(data->map[map_position.y][map_position.x] == '1')
		{
			//lengh_ray_y = ray.origin.y - pixel_position.y - 32;
			lengh_ray_y = ray.origin.y - pixel_position.y ;
			lengh_ray = (ray.direction.x * lengh_ray_y) / ray.direction.y;
			h = pow((lengh_ray), 2) + pow((lengh_ray_y), 2);
			break;
		}
		map_position.y -= 1;
		pixel_position.y -= 32;
		pixel_position.x = pixel_position.x + (32.0 * ray.direction.x / ray.direction.y);
	}
	if (h < h2)
		return (h);
	return (h2);
} */
t_collision ray_collision(t_data_global *data, t_ray ray)
{
	t_collision collision_data;
	t_fvector2 pixel_position;

	pixel_to_img(data, (t_vector2){(int)ray.origin.x, (int)ray.origin.y}, 0xFFFF00ff);
	pixel_position.x = ceil(ray.origin.x);
	pixel_position.y = ceil(ray.origin.y);
	render_rectangle(data, (t_vector2){(int)pixel_position.x - 2, (int)pixel_position.y -2}, (t_vector2){4, 4}, 0xFFAAFFff);
	while (ray.direction.x > 0 && ray.direction.y < 0)
	{
		if(data->map[(int)pixel_position.y / 32][(int)pixel_position.x / 32] == '1')
		{
			collision_data.lengh_ray = pow((pixel_position.x - (ray.origin.x)), 2) + pow(pixel_position.y - (ray.origin.y), 2);
			collision_data.horizontal_position = (int)pixel_position.y % 32;
			break;
		}
		pixel_position.x = pixel_position.x + 16;
		pixel_position.y = pixel_position.y + (16 * ray.direction.y / ray.direction.x);
		if (pixel_position.x > WIDTH || pixel_position.y > HEIGHT || pixel_position.x < 0 || pixel_position.y < 0)
			break;
		pixel_to_img(data, (t_vector2){(int)pixel_position.x, (int)pixel_position.y}, 0xFFFF00ff);
	}
	while (ray.direction.x > 0 && ray.direction.y > 0)
	{
		if(data->map[(int)pixel_position.y / 32][(int)pixel_position.x / 32] == '1')
		{
			collision_data.lengh_ray = pow((pixel_position.x - (ray.origin.x)), 2) + pow(pixel_position.y - (ray.origin.y), 2);
			collision_data.horizontal_position = (int)pixel_position.y % 32;
			break;
		}
		pixel_position.x = pixel_position.x + 16;
		pixel_position.y = pixel_position.y + (16 * ray.direction.y / ray.direction.x);
		if (pixel_position.x > WIDTH || pixel_position.y > HEIGHT || pixel_position.x < 0 || pixel_position.y < 0)
			break;
		pixel_to_img(data, (t_vector2){(int)pixel_position.x, (int)pixel_position.y}, 0xFFFF00ff);
	}
	while (ray.direction.x < 0 && ray.direction.y > 0)
	{
		if(data->map[(int)pixel_position.y / 32][(int)pixel_position.x / 32] == '1')
		{
			collision_data.lengh_ray = pow((pixel_position.x - (ray.origin.x)), 2) + pow(pixel_position.y - (ray.origin.y), 2);
			collision_data.horizontal_position = (int)pixel_position.y % 32;
			break;
		}
		pixel_position.x = pixel_position.x - 16;
		pixel_position.y = pixel_position.y + (16 * ray.direction.y / (-ray.direction.x));
		if (pixel_position.x > WIDTH || pixel_position.y > HEIGHT || pixel_position.x < 0 || pixel_position.y < 0)
			break;
		pixel_to_img(data, (t_vector2){(int)pixel_position.x, (int)pixel_position.y}, 0xFFFF00ff);
	}
	while (ray.direction.x < 0 && ray.direction.y < 0)
	{
		if(data->map[(int)pixel_position.y / 32][(int)pixel_position.x / 32] == '1')
		{
			collision_data.lengh_ray = pow((pixel_position.x - (ray.origin.x)), 2) + pow(pixel_position.y - (ray.origin.y), 2);
			collision_data.horizontal_position = (int)pixel_position.y % 32;
			break;
		}
		pixel_position.x = pixel_position.x - 16;
		pixel_position.y = pixel_position.y - (16 * (-ray.direction.y) / (-ray.direction.x));
		if (pixel_position.x > WIDTH || pixel_position.y > HEIGHT || pixel_position.x < 0 || pixel_position.y < 0)
			break;
		pixel_to_img(data, (t_vector2){(int)pixel_position.x, (int)pixel_position.y}, 0xFFFF00ff);
	}
	return (collision_data);
}
void render_ray(t_data_global *data, t_ray ray, int color, float lengh_ray)
{
	t_fvector2 index;
	t_vector2 index2;

	index.x = ceil(ray.origin.x);
	index.y = ceil(ray.origin.y);
	while((index.y >= 0 && index.y <= HEIGHT) && (index.x >= 0 && index.x <= WIDTH)
	&& ((pow(index.x - ceil(ray.origin.x), 2) + (pow(index.y - ceil(ray.origin.y), 2))) <= lengh_ray))
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
	t_collision collision_data;
	t_ray tmp_ray;
	float lengh_ray;

	(void)lengh_ray;
	data->character.camera_angle = 60;
	tmp_ray.origin.x = (data->character.position.x * 32) + 16;
	tmp_ray.origin.y = (data->character.position.y * 32) + 16;
	tmp_ray.direction = data->character.direction;
	tmp_ray.direction = Rotate(tmp_ray.direction, (-data->character.camera_angle/ 2));
	collision_data = ray_collision(data, tmp_ray);
	render_ray(data, tmp_ray, color, collision_data.lengh_ray);
	printf("hp %i\n", collision_data.horizontal_position);
	//int i = 0;
/*  	while(i < WIDTH)
	{
		lengh_ray = ray_collision(data, tmp_ray);
		render_ray(data, tmp_ray, color, lengh_ray);
		tmp_ray.direction = Rotate(tmp_ray.direction, (data->character.camera_angle / WIDTH));
		i++;
	} */
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
	render_camera(data, 0x894131ff);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	//mlx_put_image_to_window(data->mlx, data->win, data->wall.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
	return (0);
}
