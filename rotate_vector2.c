/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_vector2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastano <rcastano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:40:55 by roberto           #+#    #+#             */
/*   Updated: 2024/05/01 13:02:34 by rcastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"
/*
existia en internet en c++ creo, solo la copié y la pegué de un matemático.
No la entiendo son sumar y restar vectores se qque funciona a la perfecccion
y eso es lo unico que me importa

*/
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
