/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastano <rcastano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:01:20 by rcastano          #+#    #+#             */
/*   Updated: 2024/01/23 15:41:11 by rcastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

check_floors(t_data_global data)
{
	t_character	new_character;
	int			i;
	
	i = 0;
	data.dup_map = duplicate_map(data);
	floodfill(data.dup_map, data.character.position.x, data.character.pisition.y);
	floodfill_duplicate(data.dup_map, data.character.position.x, data.character.position.y);
	check_walls_floodfill(data);
	while (dup_map[i] != NULL)
	{
		//printf("%s\n", init->img.duplicate_map[i]);
		i++;
	}
}

int	check_character(char **map)
{
	int character;
	int	i;
	int	j;

	i = 0;
	j = 0;
	character = 0;
	while(map[i] != NULL)
	{
		while(map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'E')
				character++;
			j++;
		}
		i++;
		j = 0;
	}
	return(character);
}

check_map_validation(data)
{
	if (check_character(data.map) != 1)
		return (0);
	if (check_floors(data) /**/)
		return (0);
	return (1);
}