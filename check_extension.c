/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastano <rcastano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 01:51:53 by roberto           #+#    #+#             */
/*   Updated: 2024/05/01 12:01:48 by rcastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"
/*
	checkeamos quee el numero de argumentos sea dos
*/
int	check_argc(int argc)
{
	if (argc != 2)
		return (0);
	return (1);
}
/*
	checkeamos el nombre de la extensión, que sea ".cub"
*/
int	check_extension(char **argv)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (argv[1])
	{
		while (argv[1][i] != '\0')
		{
			if (argv[1][i] == '.' && argv[1][i + 1] == 'c'
			&& argv[1][i + 2] == 'u'
			&& argv[1][i + 3] == 'b' && argv[1][i + 4] == '\0')
				check = 1;
			i++;
		}
	}
	return (check);
}
