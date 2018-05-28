/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 14:59:48 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/24 15:00:33 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <math.h>

t_v3		v3_divide(t_v3 a, t_v3 b)
{
	t_v3	res;

	res = (t_v3){
		.x = a.x / b.x,
		.y = a.y / b.y,
		.z = a.z / b.z
	};
	return (res);
}

int			v3_to_color(t_v3 v)
{
	if (v.x > 255.0f)
		v.x = 255.0f;
	if (v.y > 255.0f)
		v.y = 255.0f;
	if (v.z > 255.0f)
		v.z = 255.0f;
	return ((int)v.z + ((int)v.y << 8) + ((int)v.x << 16));
}

float		v3_length(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

float		v3_squared_length(t_v3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_v3		v3_cross(t_v3 a, t_v3 b)
{
	t_v3	res;

	res = (t_v3){
		.x = a.y * b.z - a.z * b.y,
		.y = -(a.x * b.z - a.z * b.x),
		.z = a.x * b.y - a.y * b.x
	};
	return (res);
}
