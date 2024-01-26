/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_vector2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:40:55 by roberto           #+#    #+#             */
/*   Updated: 2024/01/26 13:57:41 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

t_fvector2 Rotate(t_fvector2 aPoint, float aDegree)
{
	float rad = aDegree * (pi / 180.0);
	float s = sin(rad);
	float c = cos(rad);

	t_fvector2 result;
	result.x = aPoint.x * c - aPoint.y * s;
	result.y = aPoint.y * c + aPoint.x * s;

	return (result);
}
