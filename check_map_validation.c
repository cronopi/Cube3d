/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastano <rcastano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:01:20 by rcastano          #+#    #+#             */
/*   Updated: 2024/05/01 12:50:06 by rcastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"
/*
llamo a las funciones de floodfill, no voy a entrar mucho en detalle porque las tratamos en el so_long que
viene a ser lo mismo, la unica diferencia es que el mapa no tiene que ser cuadrado y puede tener espacios.
*/
int	check_floors(t_data_global *data)
{
	int			i;

	i = 0;
	data->dup_map = duplicate_map(data);
	floodfill(data->dup_map, data->character.position.x, data->character.position.y);
	//floodfill_duplicate(data->dup_map, data->character.position.x, data->character.position.y);
	printf("\nel floodfill duplicado\n");
	while (data->dup_map[i] != NULL)
	{
		printf("%s", data->dup_map[i]);
		i++;
	}
	printf("\ntermina el floodfill dplicaado\n");
	check_walls_floodfill(data);
	return (1);
}
/*
compruebo que haya un personaje y nucna más de 1
*/
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
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
			{
				map[i][j] = '0';
				character++;
			}
			j++;
		}
		i++;
		j = 0;
	}
	return(character);
}

int	count_lines(t_data_global *data)
{
	int	j;

	j = 0;
	while (data->map[j] != NULL)
		j++;
	return (j);
}
/*
igual que el so_long que el mapa era valido si la ultima linea no tenia salto de linea
he hecho lo mismo. Tuve en cuenta tambien por si acaso el retorno de carro /r por si acaso
y lo dejé porque estaba más correcto así.
*/
int	check_r_and_n(t_data_global *data)
{
	int		i;
	int		j;
	size_t	check_numbers;
	unsigned int	numero;

	i = 0;
	j = count_lines(data);
	while (i < j)
	{
		check_numbers = ft_strlen(data->map[i]);
		if (data->map[i][ft_strlen(data->map[i]) - 1] == '\n')
		{
			check_numbers--;
			if (data->map[i][ft_strlen(data->map[i]) - 2] == '\r')
				check_numbers--;
		}
		numero = ft_strlen(data->map[i]);
		if (data->map[i][ft_strlen(data->map[i]) - 1] == '\n')
		{
			numero--;
			if (data->map[i][ft_strlen(data->map[i]) - 2] == '\r')
				numero--;
		}
		if (check_numbers == numero)
			i++;
		else
			return (0);
	}
	return(1);
}
/*
	se encarga de comprobar si hay personaaje
*/
int	check_posible_characters(t_data_global *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(data->map[i] != NULL)
	{
		while(data->map[i][j] != '\0')
		{
			if (data->map[i][j] != 'N' && data->map[i][j] != 'E' && data->map[i][j] != 'S' &&
				data->map[i][j] != 'W' && data->map[i][j] != '0' && data->map[i][j] != '1' &&
				data->map[i][j] != '\n' && data->map[i][j] != ' ')
			{
				printf("valor de %i %i\n", i, j);
				return (0);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return(1);
}
/*
si todas las validaciones son correctas devuelve 1 y continuamos con el programa
*/

int	check_map_validation(t_data_global *data)
{
	if(check_posible_characters(data) != 1)
	{
		printf("erroghghghr\n");
		return (0);
	}
	if (check_floors(data) != 1)
	{
		printf("error2\n");
		return (0);
	}
 	if (check_r_and_n(data) != 1)
	{
		printf("error3\n");
		return (0);
	}
	if (check_character(data->map) != 1)
	{
		printf("error4\n");
		return (0);
	}
	return (1);
}
