/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:10:34 by roberto           #+#    #+#             */
/*   Updated: 2024/06/21 13:53:08 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"
/*
aquí queremos recoger la colisión del rallo en la pared.
Para ello empezamos con el lengh ray de 0 y la posicion inicial del jugador
iniciamos un bucle por el que avanzamos el lengh ray + 0,4 y actualizamos
la posicion del rayo a la siguiente posicion.

el primer if checkea si estamos en una pared y el segundo si nos hemos salido
del tamaño de mi pantalla, en caso de hacerlo ya no encontrará más paredes y saldrá

entramos en el primer if y lo que hacemos es retroceder una "posicion" y si no estamos
dentro de la pared siginifca que la pared es horizontal, en caso contrario será vertical

la lína que calculamos lengh_ray es la distancia entre el rayo y la pared al cuadrado es decir
pitágoras pero sin hacer raiz, nos quedamso con lengh ray al cuadrado por interés.

checheamos el ray direction x para saber si la pared es a la izquierda o la derecha

y el else es lo mismo que el if pero para el ray direction y
*/
t_collision ray_collision(t_data_global *data, t_ray ray)
{
	t_collision collision_data;
	t_fvector2	pixel_position;

	collision_data.lengh_ray = 0;
	pixel_position.x = ray.origin.x;
	pixel_position.y = ray.origin.y;
	while(1)
	{
		if (data->map[(int)(pixel_position.y / 32)][(int)(pixel_position.x / 32)] == '1')
		{
			if (data->map[(int)((pixel_position.y - ray.direction.y) / 32)][(int)(pixel_position.x / 32)] == '1')
			{
				collision_data.lengh_ray = pow((pixel_position.x - (ray.origin.x)), 2) + pow(pixel_position.y - (ray.origin.y), 2);
				collision_data.horizontal_position = ((int)pixel_position.y % 32);
				if (ray.direction.x <= 0)
					collision_data.texture = 0;
				else
					collision_data.texture = 1;
				return (collision_data);
			}
			else
			{
				collision_data.horizontal_position = ((int)pixel_position.x % 32);
				collision_data.lengh_ray = pow((pixel_position.x - (ray.origin.x)), 2) + pow(pixel_position.y - (ray.origin.y), 2);
				if (ray.direction.y <= 0)
					collision_data.texture = 2;
				else
					collision_data.texture = 3;
				return (collision_data);
			}
		}
/* 		if (collision_data.lengh_ray > (HEIGHT + WIDTH))
			break; */
		pixel_position.x = pixel_position.x + ray.direction.x / 2.5;
		pixel_position.y = pixel_position.y + ray.direction.y / 2.5;
		collision_data.lengh_ray = collision_data.lengh_ray + 0.4;
	}
	collision_data.lengh_ray = -1;
	return (collision_data);
}

