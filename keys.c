/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:10:58 by roberto           #+#    #+#             */
/*   Updated: 2024/07/15 11:36:39 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"
/*
son las keys de a y d  que se encargan de rotar la camara para mirar a los lados
*/
void look_sideways_keys(int key, t_data_global *data)
{
	(void)data;
	//if (key == 123)
	if (key == 97)
	{
		data->character.direction = Rotate(data->character.direction, 5.0);
	}
	//else if (key == 124)
	if (key == 100)
	{
		data->character.direction = Rotate(data->character.direction, -5.0);
	}
}
/*
teclas para que el personaje se mueva
*/
void	movements_keys(int key, t_data_global *data) // moverse hacia alante en la direccion de la camara
{
	t_fvector2 tmp;

	//if (key == 13)
	if (key == 65362)
	{
		printf("char %c\n", data->map[(int)( (data->character.direction.x * 1) + data->character.position.x)][(int)( (data->character.direction.y * 1) + data->character.position.y)]);
		printf("la x es %i la y es %i\n", (int)((data->character.direction.x * 1) + data->character.position.x), (int)((data->character.direction.y * 1) + data->character.position.y));
		if (!(data->map[(int)((data->character.direction.x * 1) + data->character.position.x)]
			[(int)((data->character.direction.y * 1) + data->character.position.y)] == '1'))
		{
			data->character.position.x = (data->character.direction.x * 0.1) + data->character.position.x;
			data->character.position.y = (data->character.direction.y * 0.1) + data->character.position.y;
		}
	}
	//else if (key == 0)
	else if (key == 65361)
	{

		tmp = Rotate(data->character.direction, -90);
		if (!(data->map[(int)((tmp.x * 0.3) + data->character.position.x)][(int)((tmp.y * 0.3)+ data->character.position.y)] == '1'))
		{
			printf("izquieda\n");
			data->character.position.x = (tmp.x * 0.1) + data->character.position.x;
			data->character.position.y = (tmp.y * 0.1)+ data->character.position.y;
		}
	}
	//else if (key == 1)
	if (key == 65364)
	{
		if (!(data->map[(int)((tmp.x * 0.3) + data->character.position.x)][(int)((tmp.y * 0.3)+ data->character.position.y)] == '1'))
		{
			printf("s\n");
			data->character.position.x = -(data->character.direction.x * 0.1) + data->character.position.x;
			data->character.position.y = -(data->character.direction.y * 0.1)+ data->character.position.y;
		}
	}
	//else if (key == 2)
	else if (key == 65363)
	{
		tmp = Rotate(data->character.direction, 90);
		if (!(data->map[(int)((tmp.x * 0.3) + data->character.position.x)][(int)((tmp.y * 0.3)+ data->character.position.y)] == '1'))
		{
			printf("d\n");
			data->character.position.x = (tmp.x * 0.1) + data->character.position.x;
			data->character.position.y = (tmp.y * 0.1)+ data->character.position.y;
		}
	}
}

/*
la key de escape para cerraar la pantalla
*/
int	keys(int key, t_data_global *data)
{
	movements_keys(key, data);
	look_sideways_keys(key, data);
	//if (key == 53)
	if (key == 65307)
	{
		printf("Bye !\n");
		close_window(data);
	}


	return (0);
}
