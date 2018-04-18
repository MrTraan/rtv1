/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 03:44:14 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/18 03:45:36 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static t_v3	rotate_x(t_v3 v, double angle)
{
	double		c;
	double		s;
	t_v3	ret;

	c = cos((angle * M_PI) / 180.0);
	s = sin((angle * M_PI) / 180.0);
	ret.x = v.x;
	ret.y = v.y * c - v.z * s;
	ret.z = v.y * s + v.z * c;
	return (ret);
}

static t_v3	rotate_y(t_v3 v, double angle)
{
	double		c;
	double		s;
	t_v3	ret;

	c = cos((angle * M_PI) / 180.0);
	s = sin((angle * M_PI) / 180.0);
	ret.x = v.x * c + v.z * s;
	ret.y = v.y;
	ret.z = v.x * (-s) + v.z * c;
	return (ret);
}

static t_v3	rotate_z(t_v3 v, double angle)
{
	double		c;
	double		s;
	t_v3	ret;

	c = cos((angle * M_PI) / 180.0);
	s = sin((angle * M_PI) / 180.0);
	ret.x = v.x * c + v.y * (-s);
	ret.y = v.x * s + v.y * c;
	ret.z = v.z;
	return (ret);
}

t_v3		rotate(t_v3 v, t_v3 rotation)
{
	v = rotate_x(v, rotation.x);
	v = rotate_y(v, rotation.y);
	v = rotate_z(v, rotation.z);
	return (v);
}
