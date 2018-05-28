/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:01:09 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/24 15:01:22 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <math.h>

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
