/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 14:59:57 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/24 15:01:23 by ngrasset         ###   ########.fr       */
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
