/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:25 by roberto           #+#    #+#             */
/*   Updated: 2024/07/22 12:21:17 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

/*
***********************************************************************************

de número a hexadecimal
cada numero del array entre comillas corresponde con un color ya sea r g b
por como funcionan los bytes yo tengo la variable hex a la que quiero introducir
los colores en sus respectivos bytes, para ello el color del rojo se debe pushear 16 bits
a la izquierda y el color del verde 8 a la izquierda.

*/
int	number_to_hex(char **number)
{
	int hex;
	int r;
	int g;
	int b;

	r = ft_atoi(number[0]);
	g = ft_atoi(number[1]);
	b = ft_atoi(number[2]);
	hex = r;
	hex = (hex << 8) + g;
	hex = (hex << 8) + b;
	return (hex);
}
/*
	**************************************************************************
*/
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
/*
	nuestra funcion para crear rectangulos, o lo que es lo mismo,
	paredes suelos y tdo aquello que vaya a tener una textura
*/
void render_rectangle(t_data_global *data, t_vector2 coords, t_vector2 size, int color)
{
	t_vector2	limit;
	t_vector2	index;

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
/*
	renderiza el rayo en el cono de visión del pov, por cada pixel que haya en la pantalla habrá un rayo
*/
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
/*
	Asumiendo que los vectores miden 1
	obtiene la proyección de un vector sobre otro y sirve para obtener
	la diferencia entre angulos de 2 vectores(no lo entiendo bien)
	si es 1 están en la misma posicion si es 0 90 grados -1 180 grados

	https://falstad.com/dotproduct/ enlace a una página para entenderlo mejor
*/
double	get_dot_vector(t_fvector2 vector1, t_fvector2 vector2)
{
	double dot;

	dot = (vector1.x * vector2.x) + (vector1.y * vector2.y);
	return(dot);
}

/*
	obtiene el tamaño de un vector con la formula de pitágoras
	primero lo sumamos con la funcion existente, y luego raiz cuadrada
*/
double	get_magnitud(t_fvector2 vector)
{
	double magnitud;

	magnitud = get_dot_vector(vector, vector);
	magnitud = sqrt(magnitud);
	return (magnitud);
}
/*
dot y magnitud_product no se que hace hay muchas mates aquí

retorna magicamente el angulo entre dos vectores pero no entiendo
 bien como lo hace
*/
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
/*
	devuelve la altura de la pared
*/
float	get_wall_height(float lengh_ray, t_fvector2 ray_direction, t_fvector2 player_direction, int vertical_height)
{
	double	angle;
	double	corrected_distance;
	double	wall_height;

	angle = get_angle_3d(ray_direction, player_direction);
	(void) angle;
	corrected_distance = lengh_ray; //* cos(angle);
	wall_height = vertical_height / corrected_distance;
	return (wall_height * 1450);
}
/*
	*****************************************************************
	estamos poniendo la imagen correspondiente en la pared
	mientras que la pared sea menor que la altura de la ventana mantente en el bucle y que la posicion del pixel sea menor que la altura de la pared

	wall_y corresponde la posicion de la pared que se multiplica por el tamaño de la imagen que vamos a introducir en la pared y eso dividido entre la altura de la pared
	el numero que nos da hace una correlacion entre la posicion de la pared con la posicion de la imagen

	color = el ptr es una sola dimension, tenemos que pasar la coordenada y a una dimension y se hace multiplicando la posicion en y por el ancho de la imagen y a eso le sumamos
	la coordenado x que es la posicion horizontal

	el if comprueba que no salga por arriba o por abajo de la ventana y si no sale pintas el pixel y sigues aumentando en y para hacerlo con la colunma entera
	cuando sales del bucle volverás a entrar en la funcion de render img a hacer lo mismo pero con una posicion en x diferente o una mayor constantemente hasta completarlo

*/
void	render_img_in_walls(t_data_global *data, int column, float wall_height, t_collision collision_data)
{
	int color;
	int wall_y;
	int img_y;


	wall_y = 0;
	while(wall_y < (HEIGHT) && wall_y < wall_height)
	{
		img_y = wall_y * 32 / wall_height;
			color = *((int *)data->wall[collision_data.texture].ptr + ((img_y * data->wall[collision_data.texture].width) + (collision_data.horizontal_position % 32)));
			if ((HEIGHT / 2) - ((wall_height / 2) - wall_y) >= 0 && ((HEIGHT / 2) - (wall_height / 2)) <= HEIGHT)
				pixel_to_img(data, (t_vector2){column, (HEIGHT / 2) - ((wall_height / 2) - wall_y)}, color);
		wall_y++;
	}
}

/*
	creo que no hace nada porque lo usaba anteriormente para comprobar ciertas cosas
*/
/* void	render_3d(t_data_global *data, int column, t_collision collision_data, float wall_height)
{
	t_vector2 size;

	(void)collision_data;
	size.x = 1;
	size.y = wall_height;
	if (size.y < 0)
		size.y = 0;
	render_img_in_walls(data, column, wall_height, collision_data);
} */
/*
iinicaliza el "fov" de la camara a 60 grados
inicializa el origen del rayo a la posicion central del personaje

inicializa la direccion del rayo para que se corresponda con la mirada del personaje

el bucle recorra cada coordenada en el eje x de la ventana
recoge el collision_data que tiene la longitud a la que estamso de la pared, la textura correspondiente para imprimirla por pantalla


*/
void	render_camera(t_data_global *data)
{
	t_collision collision_data;
	t_ray tmp_ray;
	float	wall_height;

	data->character.camera_angle = 60;
	tmp_ray.origin.x = (data->character.position.x * 32) + 16;
	tmp_ray.origin.y = (data->character.position.y * 32) + 16;
	tmp_ray.direction = Rotate(data->character.direction, (-data->character.camera_angle/ 2));
	int i = 0;
 	while(i < WIDTH)
	{
		collision_data = ray_collision(data, tmp_ray);
		wall_height = get_wall_height(collision_data.lengh_ray, tmp_ray.direction, data->character.direction, HEIGHT);
		//render_3d(data, i, collision_data, wall_height);
		render_img_in_walls(data, i, wall_height, collision_data);
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
/*
con los colores en formato rgb llamo a la funcion number_to_hex que se encarga
 de transformarla en hexadecimal para usarla en la mlx

hacemos un rectangulo grande que corresponderá con el suelo y otro con el techo.

*/
void	render_background(t_data_global *data)
{
	int			color_floor;
	int			color_sky;
	t_vector2	coords;
	t_vector2	size;

	color_floor = number_to_hex(data->colors_floor);
	color_sky = number_to_hex(data->colors_celing);

	coords.x = 0;
	coords.y = 0;
	size.x = WIDTH;
	size.y = HEIGHT / 2;
	render_rectangle(data, coords, size, color_sky);

	coords.y = (HEIGHT / 2);
	render_rectangle(data, coords, size, color_floor);
}
/*
	el main de los renders, solo lo utilizo para llamar al resto de funciones.
*/
int	render(t_data_global *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);

	render_background(data);
	render_camera(data);
/* 	render_walls(data);
	render_character(*data);
	render_rectangle(data, (t_vector2){(int)( 32 *((data->character.direction.x * 1) + data->character.position.x)),
	(int)(32 *((data->character.direction.y * 1) + data->character.position.y))}, (t_vector2){4, 4}, 0x000000ff); */


	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
	return (0);
}
