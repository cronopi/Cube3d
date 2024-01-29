/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:10:58 by roberto           #+#    #+#             */
/*   Updated: 2024/01/29 16:35:45 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

void look_sideways_keys(int key, t_data_global *data)
{
	(void)data;
	//if (key == 123)
	if (key == 97)
	{
		data->character.direction = Rotate(data->character.direction, 1.0);
	}
	//else if (key == 124)
	if (key == 100)
	{
		data->character.direction = Rotate(data->character.direction, -1.0);
	}
}

 void	more_movements_2(int key, t_data_global *data)
{
	(void)data;
	//if (key == 1)
	if (key == 65364)
	{
		data->character.position.y = data->character.position.y + 1;
	}
	//else if (key == 2)
	else if (key == 65363)
	{
		data->character.position.x = data->character.position.x + 1;
	}
}

void	movements_keys(int key, t_data_global *data)
{
		//if (key == 13)
		if (key == 65362)
		{
			data->character.position.y = data->character.position.y - 1;
			printf("arriba\n");
		}
		//else if (key == 0)
		else if (key == 65361)
		{
			data->character.position.x = data->character.position.x - 1;
			printf("izquierda\n");
		}
		more_movements_2(key, data);
}


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
