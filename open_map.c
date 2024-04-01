/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastano <rcastano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:33:14 by roberto           #+#    #+#             */
/*   Updated: 2024/04/01 15:20:35 by rcastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

int	parser_floor_celling(char **rgb)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (rgb[j] != NULL)
	{
		printf("hola %s\n", rgb[j]);
		while (rgb[j][i] != '\0')
		{
			if ( rgb[j][i] >= '0' && rgb[j][i] <= '9' && i < 3)
				i++;
			else
			{
				printf("hay un error aqui\n");
				exit(1);
				//return (1);
			}
		}
		j++;
		i = 0;
	}
	return (0);
}

void	texture_and_color(char **map, t_data_global *data)
{
	int	i;
	int	j;
	char **spliteao;

	i = 0;
	j = 0;
	data->texture = malloc(sizeof(char *) * 5);
	data->texture[4] = NULL;
	data->colors_celing = malloc(sizeof(char *) * 4);
	data->colors_celing[3] = NULL;
	data->colors_floor = malloc(sizeof(char *) * 4);
	data->colors_floor[3] = NULL;
	while(map[j] != NULL)
	{
		while(map[j][i] != '\0')
		{
			if (map[j][i] == 'N' && map[j][i + 1] == 'O')
			{
				//hacer el split si hay . en la primera posicion posterior al espacio
				spliteao = ft_split(map[j], ' ');
				printf("hola %s\n", spliteao[1]);
				spliteao[1] = ft_strtrim(spliteao[1], "\n");
				data->texture[0] = spliteao[1];
			}
			else if (map[j][i] == 'S' && map[j][i + 1] == 'O')
			{
				spliteao = ft_split(map[j], ' ');
				printf("hola %s\n", spliteao[1]);
				spliteao[1] = ft_strtrim(spliteao[1], "\n");
				data->texture[1] = spliteao[1];
			}
			else if (map[j][i] == 'W' && map[j][i + 1] == 'E')
			{
				spliteao = ft_split(map[j], ' ');
				printf("hola %s\n", spliteao[1]);
				spliteao[1] = ft_strtrim(spliteao[1], "\n");
				data->texture[2] = spliteao[1];
			}
			else if (map[j][i] == 'E' && map[j][i + 1] == 'A')
			{
				spliteao = ft_split(map[j], ' ');
				printf("hola %s\n", spliteao[1]);
				spliteao[1] = ft_strtrim(spliteao[1], "\n");
				data->texture[3] = spliteao[1];
			}
			else if (map[j][i] == 'F' && map[j][i + 1] == ' ')
			{
				spliteao[0] = ft_strtrim(map[j], "F \n");
				data->colors_floor = ft_split(spliteao[0], ',');
				parser_floor_celling(data->colors_floor);
			}
			else if (map[j][i] == 'C' && map[j][i + 1] == ' ')
			{
				spliteao[0] = ft_strtrim(map[j], "C \n");
				data->colors_celing = ft_split(spliteao[0], ',');

				parser_floor_celling(data->colors_celing);
			}
			i++;
		}
		j++;
		i = 0;
	}
	printf("salgo\n");
}

int	parser_map(char **map)
{
	int i;
	int index;

	i = 0;
	index = 0;
	while (map[index] != NULL)
	{
		while(map[index][i] != '\0')
		{
			if (map[index][0] == '1' || map[index][0] == ' ')// habría que tener en cuenta los espacio también
				return (index);
			i++;
		}
		index++;
		i = 0;
	}
	return (index);
}

char	**open_and_return_map(char *file_name, t_data_global *data)
{
	int	i;
	int index;
	char **map;
	char **real_map;
	int fd;

	i = 0;
	index = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	while(get_next_line(fd) != NULL)
		index++;
	map = malloc(sizeof(char *) * (index + 1));
	if (!map)
		return (0);
	map[index] = NULL;
	close(fd);
	fd = open(file_name, O_RDONLY);
	while(i < index)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	index = parser_map(map);
	i = i - index;
	data->map_size.y = i + 1;
	real_map = malloc(sizeof(char *) * (data->map_size.y));
	real_map[data->map_size.y] = NULL;
	int count = 0;
	while(map[index])
	{
		real_map[count] = ft_strdup(map[index]);
		index++;
		count++;
	}
	/*
	count = 0;
	while (real_map[count] != NULL)
	{
		printf("%s", real_map[count]);
		count++;
	} */
	texture_and_color(map, data);
	return (real_map);
}
