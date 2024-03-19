/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastano <rcastano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:33:14 by roberto           #+#    #+#             */
/*   Updated: 2024/03/19 13:54:27 by rcastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

void	parser_floor_celling(char **map, int k, int j)
{
	int	l;
	int	coma;

	l = 0;
	coma = 0;
	while (map[j][k])
	{
		l = 0;
		while (map[j][k] >= '0' && map[j][k] >= '9')
		{
			if (l > 4)
			{
				printf("tamal");
				exit(1);
			}
			k++;
			l++;
		}
		if ((map[j][k] == ',') && (map[j][k - 1] >= '0' && map[j][k - 1] <= '9') && (map[j][k + 1] >= '0' && map[j][k + 1] <= '9'))
		{
			if (coma > 2)
			{
				printf("ta mal coma");
				exit(1);
			}
			coma++;
			k++;
		}
	}
}

void	texture_and_color(char **map, t_data_global *data)
{
	int	i;
	int	j;
	char **spliteao;
//	int k;

	i = 0;
	j = 0;
	data->texture = malloc(sizeof(char *) * 5);
	data->texture[4] = NULL;
	data->colors = malloc(sizeof(char *) * 3);
	data->colors[2] = NULL;
	while(map[j] != NULL)
	{
		while(map[j][i] != '\0')
		{
			if (map[j][i] == 'N' && map[j][i + 1] == 'O')
			{
				//hacer el split si hay . en la primera posicion posterior al espacio
				spliteao = ft_split(map[j], ' ');
				printf("hola %s\n", spliteao[1]);
				data->texture[0] = spliteao[1];
			}
			else if (map[j][i] == 'S' && map[j][i + 1] == 'O')
			{
				spliteao = ft_split(map[j], ' ');
				printf("hola %s\n", spliteao[1]);
				data->texture[1] = spliteao[1];
			}
			else if (map[j][i] == 'W' && map[j][i + 1] == 'E')
			{
				spliteao = ft_split(map[j], ' ');
				printf("hola %s\n", spliteao[1]);
				data->texture[2] = spliteao[1];
			}
			else if (map[j][i] == 'E' && map[j][i + 1] == 'A')
			{
				spliteao = ft_split(map[j], ' ');
				printf("hola %s\n", spliteao[1]);
				data->texture[3] = spliteao[1];
			}
/* 			else if (map[j][i] == 'F' && map[j][i + 1] == ' ')
			{
				spliteao = ft_split(map[j], ' ');
				//k = i + 2;
				//parser_floor_celling(map, k, j);
				printf("hola %s\n", spliteao[1]);
				data->colors[0] = spliteao[1];
			}
			else if (map[j][i] == 'C' && map[j][i + 1] == ' ')
			{
				spliteao = ft_split(map[j], ' ');
				printf("hola %s\n", spliteao[1]);
				//k = i + 2;
				//parser_floor_celling(map, k, j);
				data->colors[1] = spliteao[1];
			} */
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
			if (map[index][0] == '1')// habría que tener en cuenta los espacio también
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
