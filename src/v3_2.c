/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:00:40 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/24 15:01:04 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <math.h>

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
