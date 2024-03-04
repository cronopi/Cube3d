/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:08:20 by roberto           #+#    #+#             */
/*   Updated: 2024/03/04 11:11:56 by roberto          ###   ########.fr       */
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
	//float	x;
	double	x;
	//float	y;
	double	y;
}				t_fvector2;

typedef struct s_ray
{
	t_fvector2 origin;
	t_fvector2 direction;
}				t_ray;

typedef struct s_collision
{
	float	lengh_ray;
	int		horizontal_position;
	char	direction;

}				t_collision;

typedef struct s_character
{
	t_fvector2	position;
	t_fvector2	direction;
	float		camera_angle;
}				t_character;

typedef struct s_img
{
	void	*img;
	void	*ptr;
	int		width;
	int		height;
	int		bpp;
	int		stride;
	int		endian;
}				t_img;

typedef struct s_data_global
{
	t_vector2		map_size;
	t_img			wall;
	void			*img;
	void			*mlx;
	void			*win;
	char			**map;
	char			**dup_map;
	t_character		character;
}				t_data_global;

t_collision ray_collision(t_data_global *data, t_ray ray);
t_character initialize_character(char **map);
int		render(t_data_global *data);
int		keys(int key, t_data_global *init);
int		close_window(t_data_global *init);
int		check_argc(int argc);
int		check_extension(char **argv);
int		check_map_validation(t_data_global *data);
char	**open_and_return_map(char *file_name, t_data_global *data);
void	floodfill(char **duplicate, int x, int y);
void	floodfill_duplicate(char **duplicate, int x, int y);
char	**duplicate_map(t_data_global *data);
void	check_walls_floodfill(t_data_global *data);
t_fvector2 Rotate(t_fvector2 aPoint, float aDegree);

# endif
