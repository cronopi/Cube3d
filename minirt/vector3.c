/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberto <roberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:44:05 by roberto           #+#    #+#             */
/*   Updated: 2023/12/31 23:41:36 by roberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

t_vector3	vector3_sumar(t_vector3 vector1, t_vector3 vector2)
{
	t_vector3	new;

	new.x = vector1.x + vector2.x;
	new.y = vector1.y + vector2.y;
	new.z = vector1.z + vector2.z;
	return (new);
}

t_vector3	vector3_restar(t_vector3 vector1, t_vector3 vector2)
{
	t_vector3	new;

	new.x = vector1.x - vector2.x;
	new.y = vector1.y - vector2.y;
	new.z = vector1.z - vector2.z;
	return (new);
}

t_vector3	vector3_multiplicar(t_vector3 vector1, t_vector3 vector2)
{
	t_vector3	new;

	new.x = vector1.x * vector2.x;
	new.y = vector1.y * vector2.y;
	new.z = vector1.z * vector2.z;
	return (new);
}

t_vector3	vector3_dividir(t_vector3 vector1, t_vector3 vector2)
{
	t_vector3	new;

	new.x = vector1.x / vector2.x;
	new.y = vector1.y / vector2.y;
	new.z = vector1.z / vector2.z;
	return (new);
}

t_vector3	vector3_float_multiplicar(t_vector3 vector, float number)
{
	t_vector3	new;

	new.x = vector.x * number;
	new.y = vector.y * number;
	new.z = vector.z * number;
	return (new);
}

t_vector3	vector3_float_dividir(t_vector3 vector, float number)
{
	t_vector3	new;

	new.x = vector.x / number;
	new.y = vector.y / number;
	new.z = vector.z / number;
	return (new);
}

double	vector3_dot(t_vector3 vector1, t_vector3 vector2)
{
	t_vector3	new;

	new.x = vector1.x * vector2.x;
	new.y = vector1.y * vector2.y;
	new.z = vector1.z * vector2.z;
	return (new.x + new.y + new.z);
}

