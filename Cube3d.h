/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:08:20 by roberto           #+#    #+#             */
/*   Updated: 2024/02/02 09:27:48 by roberto          ###   ########.fr       */
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
//# include <mlx.h>

# define WIDTH 640
# define HEIGHT 600
# define pi 3.14159264

typedef struct s_vector2
{
	int	x;
	int	y;
}				t_vector2;

typedef struct s_fvector2
{
	float	x;
	float	y;
}				t_fvector2;

typedef struct s_ray
{
	t_fvector2 origin;
	t_fvector2 direction;
}				t_ray;

typedef struct s_character
{
	t_fvector2	position;
	t_fvector2	direction;
	float		camera_angle;
}				t_character;

typedef struct s_data_global
{
	void 			*img;
	void			*mlx;
	void			*win;
	char			**map;
	char			**dup_map;
	t_character		character;
}				t_data_global;

t_character initialize_character(char **map);
int		render(t_data_global *data);
int		keys(int key, t_data_global *init);
int		close_window(t_data_global *init);
int		check_argc(int argc);
int		check_extension(char **argv);
int		check_map_validation(t_data_global *data);
char	**open_and_return_map(char *file_name);
void	floodfill(char **duplicate, int x, int y);
void	floodfill_duplicate(char **duplicate, int x, int y);
char	**duplicate_map(t_data_global *data);
void	check_walls_floodfill(t_data_global *data);
t_fvector2 Rotate(t_fvector2 aPoint, float aDegree);

# endif
