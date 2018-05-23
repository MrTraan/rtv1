/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 13:24:39 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/23 17:38:33 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <math.h>

t_v3		v3_add(t_v3 a, t_v3 b)
{
	t_v3	res;

	res = (t_v3){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	};
	return (res);
}

t_v3		v3_sub(t_v3 a, t_v3 b)
{
	t_v3	res;

	res = (t_v3){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	};
	return (res);
}

t_v3		v3_add_float(t_v3 a, float f)
{
	t_v3	res;

	res = (t_v3){
		.x = a.x + f,
		.y = a.y + f,
		.z = a.z + f
	};
	return (res);
}

t_v3		v3_mul_float(t_v3 a, float f)
{
	t_v3	res;

	res = (t_v3){
		.x = a.x * f,
		.y = a.y * f,
		.z = a.z * f
	};
	return (res);
}

t_v3		v3_mul(t_v3 a, t_v3 b)
{
	t_v3	res;

	res = (t_v3){
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z
	};
	return (res);
}

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

t_v3		v3_unit(t_v3 src)
{
	t_v3		res;
	float		length;

	length = v3_length(src);
	if (length == 0)
		return ((t_v3){0, 1, 0});
	res = (t_v3){
		.x = src.x / length,
		.y = src.y / length,
		.z = src.z / length
	};
	return (res);
}

t_v3		v3_reverse(t_v3 src)
{
	return ((t_v3){-(src.x), -(src.y), -(src.z)});
}

float		v3_dot(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_v3		v3_rot_x(t_v3 src, float angle)
{
	return ((t_v3) {
		.x = src.x,
		.y = src.y * cosf(angle) - src.z * sinf(angle),
		.z = src.y * sinf(angle) + src.z * cosf(angle),
	});
}

t_v3		v3_rot_y(t_v3 src, float angle)
{
	return ((t_v3) {
		.x = src.x * cosf(angle) + src.z * sinf(angle),
		.y = src.y,
		.z = -src.x * sinf(angle) + src.z * cosf(angle),
	});
}

t_v3		v3_rot_z(t_v3 src, float angle)
{
	return ((t_v3) {
		.x = src.x * cosf(angle) - src.y * sinf(angle),
		.y = src.x * sinf(angle) + src.y * cosf(angle),
		.z = src.z,
	});
}

t_v3		v3_rot(t_v3 src, t_v3 rotation)
{
	src = v3_rot_x(src, rotation.x);
	src = v3_rot_y(src, rotation.y);
	src = v3_rot_z(src, rotation.z);
	return (src);
}
