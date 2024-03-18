/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:33:14 by roberto           #+#    #+#             */
/*   Updated: 2024/03/18 12:53:41 by roberto          ###   ########.fr       */
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
void	texture_and_color(char **map)
{
	int	i;
	int	j;
	int k;
	char **texture;
	char **colors;


	i = 0;
	j = 0;
	texture = malloc(sizeof(char *) * 5);
	texture[4] = NULL;
	colors = malloc(sizeof(char *) * 3);
	colors[2] = NULL;

	while(map[j] != NULL)
	{
		while(map[j][i] != '\0')
		{
			if (map[j][i] == 'S' && map[j][i + 1] == 'O')
				texture[0] = ft_strdup(map[j]);
			else if (map[j][i] == 'N' && map[j][i + 1] == 'O')
				texture[1] = ft_strdup(map[j]);
			else if (map[j][i] == 'W' && map[j][i + 1] == 'E')
				texture[2] = ft_strdup(map[j]);
			else if (map[j][i] == 'E' && map[j][i + 1] == 'A')
				texture[3] = ft_strdup(map[j]);
			else if (map[j][i] == 'F' && map[j][i + 1] == ' ' && (map[j][i + 2] >= '0' && map[j][i + 2] <= '9' ))
			{
				k = i + 2;
				parser_floor_celling(map, k, j);
				colors[0] = ft_strdup(map[j]);
			}
			else if (map[j][i] == 'C' && map[j][i + 1] == ' ' && (map[j][i + 2] >= '0' && map[j][i + 2] <= '9' ))
			{
				k = i + 2;
				parser_floor_celling(map, k, j);
				colors[1] = ft_strdup(map[j]);
			}


/* 			if (map[j][i] == ' ')
				i++;
			else */
				i++;
		}
		j++;
		i = 0;
	}
}

char	**open_and_return_map(char *file_name, t_data_global *data)
{
	int	i;
	int index;
	char **map;
	char **map2;
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
	int count = 0;
	i = 0;
	index = 0;
	while (map[index] != NULL)
	{
		while (map[index][i] != '\0')
		{
			if (map[index][0] == '1')
			{
				index++;
				count++;
			}
			i++;

		}


		i = 0;
		index++;
	}
	i = 0;
	index = 0;
	map2 = malloc (sizeof(char *) * (6 + 1));
	map[6] = NULL;
	while (map[index] != NULL)
	{
		printf("AAAAAAAAAAAAAAAAAAAAA\n %s", map[index]);
		map[index] = ft_strdup(map2[index]);
		index++;
	}
	index = 0;
	while(map[index] != NULL)
	{
		printf("%s", map[index]);
		index++;
	}
	data->map_size.y = i;
	//texture_and_color(map);
	exit(1);
	return (map);
}
