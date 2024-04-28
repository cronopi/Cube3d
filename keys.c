/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:10:58 by roberto           #+#    #+#             */
/*   Updated: 2024/04/18 11:05:17 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

void look_sideways_keys(int key, t_data_global *data)
{
	(void)data;
	if (key == 123)
	//if (key == 97)
	{
		data->character.direction = Rotate(data->character.direction, 5.0);
	}
	else if (key == 124)
	//if (key == 100)
	{
		data->character.direction = Rotate(data->character.direction, -5.0);
	}
}

void	movements_keys(int key, t_data_global *data) // moverse hacia alante en la direccion de la camara
{
	t_fvector2 tmp;

	if (key == 13)
	//if (key == 65362)
	{
		printf("w\n");
		data->character.position.x = (data->character.direction.x * 0.1) + data->character.position.x;
		data->character.position.y = (data->character.direction.y * 0.1)+ data->character.position.y;
	}
	else if (key == 0)
	//else if (key == 65361)
	{
		printf("a\n");
		tmp = Rotate(data->character.direction, -90);
		data->character.position.x = (tmp.x * 0.1) + data->character.position.x;
		data->character.position.y = (tmp.y * 0.1)+ data->character.position.y;
	}
	else if (key == 1)
	//if (key == 65364)
	{
		printf("s\n");
		data->character.position.x = -(data->character.direction.x * 0.1) + data->character.position.x;
		data->character.position.y = -(data->character.direction.y * 0.1)+ data->character.position.y;
	}
	else if (key == 2)
	//else if (key == 65363)
	{
		printf("d\n");
		tmp = Rotate(data->character.direction, 90);
		data->character.position.x = (tmp.x * 0.1) + data->character.position.x;
		data->character.position.y = (tmp.y * 0.1)+ data->character.position.y;
	}
}


int	keys(int key, t_data_global *data)
{
	movements_keys(key, data);
	look_sideways_keys(key, data);
	if (key == 53)
	//if (key == 65307)
	{
		printf("Bye !\n");
		close_window(data);
	}


	return (0);
}
