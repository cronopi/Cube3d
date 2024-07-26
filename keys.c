/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:10:58 by roberto           #+#    #+#             */
/*   Updated: 2024/07/26 10:07:23 by roberto          ###   ########.fr       */
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
	float x = 0;
	float y = 0;
	t_fvector2 tmp;


	if (key == 65362)
	{
		printf("empieza la impresion\n");

		int count = 0;
		while (data->map[count] != NULL)
		{
			printf("%s", data->map[count]);
			count++;
		}
		printf("termina la impresion\n");
		x = (data->character.direction.x * 1.3) + data->character.position.x + 0.5;
		y = (data->character.direction.y * 1.3) + data->character.position.y + 0.5;
		printf("la x:%f la y:%f\n", x, y);
		printf("character position x:%f y:%f\n", data->character.position.x, data->character.position.y);
		printf("la x:%i la y:%i\n", (int)x, (int)y);
		printf("dta map :%c\n", data->map[(int)y][(int)x]);
		if (!(data->map[(int)(y)][(int)(x)] == '1'))
		{
			data->character.position.x = (data->character.direction.x * 0.1) + data->character.position.x;
			data->character.position.y = (data->character.direction.y * 0.1) + data->character.position.y;
		}
	}
	else if (key == 65361)
	{
		tmp = Rotate(data->character.direction, -90);
		x = (tmp.x * 1.3) + data->character.position.x + 0.5;
		y = (tmp.y * 1.3) + data->character.position.y + 0.5;
		if (!(data->map[(int)(y)][(int)(x)] == '1'))
		{
			printf("izquieda\n");
			data->character.position.x = (tmp.x * 0.1) + data->character.position.x;
			data->character.position.y = (tmp.y * 0.1)+ data->character.position.y;
		}
	}
	if (key == 65364)
	{
		tmp = Rotate(data->character.direction, -180);
		x = (tmp.x * 1.3) + data->character.position.x + 0.5;
		y = (tmp.y * 1.3) + data->character.position.y + 0.5;
		if (!(data->map[(int)(y)][(int)(x)] == '1'))
		{
			printf("s\n");
			data->character.position.x = -(data->character.direction.x * 0.1) + data->character.position.x;
			data->character.position.y = -(data->character.direction.y * 0.1)+ data->character.position.y;
		}
	}
	else if (key == 65363)
	{
		tmp = Rotate(data->character.direction, 90);
		x = (tmp.x * 1.3) + data->character.position.x + 0.5;
		y = (tmp.y * 1.3) + data->character.position.y + 0.5;
		if (!(data->map[(int)(y)][(int)(x)] == '1'))
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
