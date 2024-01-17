/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:33:14 by roberto           #+#    #+#             */
/*   Updated: 2024/01/15 12:51:41 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

char	**open_and_return_map(char *file_name)
{
	int	i;
	int index;
	char **map;
	int fd;

	i = 0;
	index = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);

	while(get_next_line(fd) != NULL)
		index++;
	printf("%d\n", index);
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
	i = 0;
	while (i < 4)
	{
		printf("%s", map[i]);
		i++;
	}
	return (map);
}
