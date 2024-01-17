/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:08:20 by roberto           #+#    #+#             */
/*   Updated: 2024/01/17 16:06:10 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "mlx/mlx.h"
# include "Vector3.h"
//# include <mlx.h>

# define WIDTH 920
# define HEIGHT 540

typedef struct s_vector2
{
	int	x;
	int	y;
}				t_vector2;

typedef struct s_ray
{
	t_vector2 origin;
	t_vector2 direction;
}				t_ray;

typedef struct s_character
{
	t_vector2	position;
	t_vector2	direction;
	float		camera_angle;// 2 * atan(0.66/1.0);
}				t_character;

typedef struct s_data_global
{
	void 			*img;
	void			*mlx;
	void			*win;
	char			**map;
	t_character		character;
}				t_data_global;

t_character initialize_character(char **map);
int		render(t_data_global *data);
int		keys(int key, t_data_global *init);
int		close_window(t_data_global *init);
int		check_extension(char **argv);
char	**open_and_return_map(char *file_name);

# endif
