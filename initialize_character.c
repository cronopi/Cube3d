/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_character.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:30:10 by roberto           #+#    #+#             */
/*   Updated: 2024/01/26 14:02:09 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

t_character character_start_and_direction(char **map)
{
	int i;
	int j;
	t_character new_character;

	i = 0;
	j = 0;
	while(map[i] != NULL)
	{
		while(map[i][j] != '\0')
		{
			if (map[i][j] == 'N')
			{
				new_character.position = (t_fvector2){j,i};
				new_character.direction = (t_fvector2){0,-1};
			}
			else if (map[i][j] == 'S')
			{
				new_character.position = (t_fvector2){j,i};
				new_character.direction = (t_fvector2){0,1};
			}
			else if (map[i][j] == 'E')
			{
				new_character.position = (t_fvector2){j,i};
				new_character.direction = (t_fvector2){1,0};
			}
			else if (map[i][j] == 'W')
			{
				new_character.position = (t_fvector2){j,i};
				new_character.direction = (t_fvector2){-1,0};
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (new_character);
}

t_character	initialize_character(char **map)
{
	t_character new_character;

	new_character = character_start_and_direction(map);
	//printf("esto vale la posicion %i %i la direccion es %i %i\n", new_character.position.x, new_character.position.y,new_character.direction.x, new_character.direction.y);
	new_character.camera_angle = 0;

	return (new_character);
}
