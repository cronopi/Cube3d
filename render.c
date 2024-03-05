/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:25 by roberto           #+#    #+#             */
/*   Updated: 2024/03/05 16:59:08 by roberto          ###   ########.fr       */
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
	t_vector2	limit;
	t_vector2	index;

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

double	get_dot_vector(t_fvector2 vector1, t_fvector2 vector2)
{
	double dot;

	dot = (vector1.x * vector2.x) + (vector1.y * vector2.y);
	return(dot);
}

double	get_magnitud(t_fvector2 vector)
{
	double magnitud;

	magnitud = get_dot_vector(vector, vector);
	magnitud = sqrt(magnitud);
	return (magnitud);
}

float	get_angle_3d(t_fvector2 vector1, t_fvector2 vector2)
{
	float dot;
	float magnitud_product;

	dot = get_dot_vector(vector1, vector2);
	magnitud_product = get_magnitud(vector1) * get_magnitud(vector2);
	if (magnitud_product == 0)
		return (0);
	return (dot / magnitud_product);
}

float	get_wall_height(float lengh_ray, t_fvector2 ray_direction, t_fvector2 player_direction, int vertical_height)
{
	double angle;
	double	corrected_distance;
	double	wall_height;
	angle = get_angle_3d(ray_direction, player_direction);
	(void) angle;
	corrected_distance = lengh_ray; //* cos(angle);
	wall_height = vertical_height / corrected_distance;
	return (wall_height * 1450);
}

void	render_img_in_walls(t_data_global *data, int column, float wall_height, int horizontal)
{
	int color;
	int i;
	int j;

	i = 0;
	while(i < wall_height)
	{
		j = i * 32 / wall_height;
		color = *((int *)data->wall.ptr + ((j * data->wall.width) + (horizontal % 32)));
		pixel_to_img(data, (t_vector2){column,  (HEIGHT / 2) - ((wall_height / 2) - i)}, color);
		i++;
	}
}
void	render_3d(t_data_global *data, int column, t_collision collision_data, float wall_height)
{
	t_vector2 coords;
	t_vector2 size;

	(void)collision_data;
	(void)coords;
	if (wall_height >= HEIGHT)
		wall_height = HEIGHT;
	coords.y = (HEIGHT / 2) - (wall_height / 2);
	coords.x = column;
	size.x = 1;
	size.y = wall_height;
	if (size.y < 0)
		size.y = 0;
	if (collision_data.direction == 'N')
	{
		render_img_in_walls(data, column, wall_height, collision_data.horizontal_position);
		//render_rectangle(data, coords, size, 0x0000ff);
	}
	else if (collision_data.direction == 'S')
		render_rectangle(data, coords, size, 0x00ff00);
	else if (collision_data.direction == 'E')
		render_rectangle(data, coords, size, 0xff0000);
	else if (collision_data.direction == 'O')
		render_rectangle(data, coords, size, 0xffff00);
}

void	render_camera(t_data_global *data, int color)
{
	t_collision collision_data;
	t_ray tmp_ray;
	float lengh_ray;
	float	wall_height;

	(void)lengh_ray;
	data->character.camera_angle = 60;
	tmp_ray.origin.x = (data->character.position.x * 32) + 16;
	tmp_ray.origin.y = (data->character.position.y * 32) + 16;
	tmp_ray.direction = data->character.direction;
	tmp_ray.direction = Rotate(tmp_ray.direction, (-data->character.camera_angle/ 2));
	//printf("hp %i\n", collision_data.horizontal_position);
	int i = 0;
 	while(i < WIDTH)
	{
		collision_data = ray_collision(data, tmp_ray);
		wall_height = get_wall_height(collision_data.lengh_ray, tmp_ray.direction, data->character.direction, HEIGHT);
		render_3d(data, i, collision_data, wall_height);
		render_ray(data, tmp_ray, color, collision_data.lengh_ray);
		tmp_ray.direction = Rotate(tmp_ray.direction, (data->character.camera_angle / WIDTH));
		i++;
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

void	render_background(t_data_global *data)
{
	int			color_floor;
	int			color_sky;
	t_vector2	coords;
	t_vector2	size;

	color_sky = 0x0000ffff;
	color_floor = 0x8B4513ff;
	coords.x = 0;
	coords.y = 0;
	size.x = WIDTH;
	size.y = HEIGHT / 2;
	render_rectangle(data, coords, size, color_sky);

	coords.y = (HEIGHT / 2);
	size.y = (HEIGHT / 2);
	render_rectangle(data, coords, size, color_floor);
}

int	render(t_data_global *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);

	render_background(data);
	render_walls(data);
	render_character(*data);
	render_camera(data, 0x894131ff);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->wall.img, 1, 1);
	mlx_destroy_image(data->mlx, data->img);
	return (0);
}
