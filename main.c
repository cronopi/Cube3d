/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:20:26 by rcastano          #+#    #+#             */
/*   Updated: 2024/05/10 10:33:06 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

void	close_program(t_data_global *data)
{
	//free_double_pointer(init);
	//mlx_destroy_display(init->mlx);// no se puede usar en macOS
	free(data->mlx);
}
int	close_window(t_data_global *data)
{
	mlx_destroy_window(data->mlx, data->win);
	close_program(data);
	exit(0);
	return (0);
}
void	leaks(void)
{
	system("leaks -q Cube3d");
}
void	print_map(char **map)
{
	int i;

	i = 0;
	while(map[i] != NULL)
	{
		printf("%s", map[i]);
		i++;
	}
	printf("\nfin de impresion del mapa\n");
}
/*
se encarga de cargar las imagenes de las paredes para luego imprimirlas por pantalla en el juego.

&(data->wall[0].width), &(data->wall[0].height) se rellena con la altura y anchura de la imagen que se abre

data->wall[i].ptr es la direccion del primer pixel

bpp = bits por pixel
stride = tamaño de la imagen
endian = si el orden de los datos va en direccion o en contra de la memoria

el bucle

get_data_adrr retorna el puntero al primer pixel, a parte de rellenar otros datos
luego con los datos obtenidos en bpp width y height

primero tenemos (8)bits y bpp lo queremos en (1)bytes porque estamos trabajando en bytes

en el width y height calculamos el stride entre los bytes para saber el "tamaño real" de la imagen y tenerlo todo en bytes
*/
void	set_up_texture_map(t_data_global *data)
{
	int	i;

	i = 0;
	if ((data->wall[0].img = mlx_xpm_file_to_image(data->mlx, data->texture[0], &(data->wall[0].width), &(data->wall[0].height))) == NULL)
	{
		printf("error1\n");
		exit (1);
	}
		if ((data->wall[1].img = mlx_xpm_file_to_image(data->mlx, data->texture[1], &(data->wall[1].width), &(data->wall[1].height))) == NULL)
	{
		printf("error1\n");
		exit (1);
	}
	if ((data->wall[2].img = mlx_xpm_file_to_image(data->mlx, data->texture[2], &(data->wall[2].width), &(data->wall[2].height))) == NULL)
	{
		printf("error1\n");
		exit (1);
	}
	if ((data->wall[3].img = mlx_xpm_file_to_image(data->mlx, data->texture[3], &(data->wall[3].width), &(data->wall[3].height))) == NULL)
	{
		printf("error1\n");
		exit (1);
	}
	while (i < 4)
	{
		if ((data->wall[i].ptr = mlx_get_data_addr(data->wall[i].img, &data->wall[i].bpp, &data->wall[i].stride, &data->wall[i].endian)) == NULL)
		{
			printf("error2\n");
			exit (1);
		}
		data->wall[i].bpp /= 8;
		data->wall[i].width = data->wall[i].stride / data->wall[i].bpp;
		data->wall[i].height = data->wall[i].stride / data->wall[i].bpp;
		i++;
	}
}
/*
llamamos a argumentos y las extensiones

despues open_and_return_map devolverá el mapa
inizialize_character inicializará el personaje

check_map_validation valida el mapa y todo su contenido

set_up_texture_map cargará las texturas de las paredes

despues de setear la mlx básica entraremos en los hook y la primera funcion es render.
Es basicamente el ejercicio entero, no lo entiendo ni yo.

keys recoge las teclas que necesiitamos para movernos y la camara, cerrar la pantalla etc.

*/
int	main(int argc, char **argv)
{
	t_data_global	data;

	if (check_argc(argc) == 0)
		return (1);
	if (check_extension(argv) == 0)
		return (1);
	data.map = open_and_return_map(argv[1], &data);
	if (data.map == NULL)
	{
		printf("hay un error en la apertura del mapa\n");
		return (1);
	}
	print_map(data.map);
	data.character = initialize_character(data.map);
	if (check_map_validation(&data) == 0)
	{
		printf("hay un error de validez en el mapa");
		return (1);
	}
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cube3D");
	if (data.win == NULL)
	{
		//free_double_pointer(&init);
		return (1);
	}
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	set_up_texture_map(&data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, 2, 1L << 0, keys, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx);
	close_window(&data);
	return (0);
}
