/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:10:34 by roberto           #+#    #+#             */
/*   Updated: 2024/03/04 11:35:44 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

/* t_collision ray_collision(t_data_global *data, t_ray ray)
{
	t_collision collision_data;
	t_fvector2	pixel_position; // current check

	collision_data.lengh_ray = 0;
	pixel_position.x = ray.origin.x;
	pixel_position.y = ray.origin.y;

	while(1)
	{
		if (data->map[(int)(pixel_position.y / 32)][(int)(pixel_position.x / 32)] == '1')
		{
			if (data->map[(int)((pixel_position.y - ray.direction.y) / 32)][(int)(pixel_position.x / 32)] == '1')
			{
				collision_data.horizontal_position = ((int)pixel_position.y % 32);
				if (ray.direction.x <= 0)
					collision_data.direction = 'O';
				else
					collision_data.direction = 'E';
				return (collision_data);
			}
			else
			{
				collision_data.horizontal_position = ((int)pixel_position.x % 32);
				if (ray.direction.y <= 0)
					collision_data.direction = 'N';
				else
					collision_data.direction = 'S';
				return (collision_data);
			}
		}
		pixel_position.x = pixel_position.x + ray.direction.x / 2.5;
		pixel_position.y = pixel_position.y + ray.direction.y / 2.5;
		collision_data.lengh_ray = collision_data.lengh_ray + 0.4;
	}
}*/


/*    loop {
        if map[(current_check.y / 32.0) as usize][(current_check.x / 32.0) as usize] == '1' {
            if map [((current_check.y - ray.direction.y) / 32.0) as usize][(current_check.x / 32.0) as usize] == '1' {
                collision.horizontal = current_check.y % 32.0;
            }
            else
            {
                collision.horizontal = current_check.x % 32.0;
            }
            return collision;
        }
        current_check = current_check + ray.direction.clone() / 2.5;
        collision.lenght += 0.4;
    } */
