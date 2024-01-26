/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:20:26 by rcastano          #+#    #+#             */
/*   Updated: 2024/01/25 12:30:14 by roberto          ###   ########.fr       */
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
	exit(1);
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
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data_global	data;

	if (check_argc(argc) == 0)
		return (0);
	if (check_extension(argv) == 0)
		return (0);

	data.map = open_and_return_map(argv[1]);
	print_map(data.map);
	data.character = initialize_character(data.map);

	if (check_map_validation(&data) == 0)
	{
		printf("hay un error de validez en el mapa");
		return (0);
	}
/* 	printf("\nel duplicado\n");
	int i = 0;
	while (data.dup_map[i] != NULL)
	{
		printf("%s", data.dup_map[i]);
		i++;
	}
	printf("\nfin duplicado\n"); */
	data.mlx = mlx_init();
	if (!data.mlx)
		return (0);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cube3D");
	if (data.win == NULL)
	{
		//free_double_pointer(&init);
		return (0);
	}
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);

	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, 2, 1L << 0, keys, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx);
	close_window(&data);
	return (0);
}
