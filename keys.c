/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:10:58 by roberto           #+#    #+#             */
/*   Updated: 2024/02/02 09:29:20 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

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

void	movements_keys(int key, t_data_global *data)
{
		//if (key == 13)
		if (key == 65362)
		{
			data->character.position.y = data->character.position.y - 1;
		}
		//else if (key == 0)
		else if (key == 65361)
		{
			data->character.position.x = data->character.position.x - 1;
		}
		//else if (key == 1)
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
