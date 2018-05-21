/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:26:09 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/13 13:32:14 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>
/* static t_v3		cone_normal(t_cone *cone, t_v3 point) */
/* { */
/* 	t_v3		normal; */

/* 	normal.x = point.x; */
/* 	normal.y = 0.1 * point.y; */
/* 	normal.z = point.z; */
/* 	normal = rotate(normal, cone->direction); */
/* 	return (v3_unit(normal)); */
/* } */

char			ray_hit_cone(t_cone *cone, t_ray ray, t_v2 t_min_max, t_hit_record *rec)
{
	float		discriminant;
	float 		temp;
	float 		a;
	float 		b;
	float 		c;
	float 		k = tan(cone->alpha * M_PI / 180 / 2);


	t_v3 x = v3_sub(ray.origin, cone->origin);
	float m = v3_dot(ray.direction, cone->direction) + v3_dot(x, cone->direction);

	a = v3_dot(ray.direction, ray.direction) - (1 + k * k) * pow(v3_dot(ray.direction, cone->direction), 2);
	b = 2 * v3_dot(ray.direction, x) - (1 + k * k) * v3_dot(ray.direction, cone->direction) * v3_dot(x, cone->direction);
	c = v3_dot(x, x) - (1 + k * k) * pow(v3_dot(x, cone->direction), 2);

	t_v3	e;
	t_v3	d;
	t_v3	v;

	e = v3_rot(v3_sub(ray.origin, cone->origin), cone->direction);
	d = v3_rot(ray.direction, cone->direction);
	v.x = (d.x * d.x) + (d.z * d.z) - (d.y * d.y * k);
	v.y = 2 * ((e.x * d.x) + (e.z * d.z)) - 2 * (e.y * d.y * k);
	v.z = (e.x * e.x) + (e.z * e.z) - (e.y * e.y) * k;
	a = v.x;
	b = v.y;
	c = v.z;


	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	temp = ((-b - sqrt(discriminant)) / (2.0 * a));
	if (temp < t_min_max.x || temp > t_min_max.y)
		temp = ((-b + sqrt(discriminant)) / (2.0 * a));
	if (temp < t_min_max.x || temp > t_min_max.y)
		return (0);
	/* if (v3_length(v3_sub(ray_point_at_parameter(ray, temp), cone->origin)) > 2) */
	/* 	return (0); */
	rec->t = temp;
	rec->p = ray_point_at_parameter(ray, temp);	
	rec->normal = v3_unit(v3_sub(
			v3_sub(rec->p, cone->origin),
			v3_mul_float(cone->direction, (1 + k * k) * m)
			));
	rec->normal = v3_rot(rec->normal, cone->direction);
	rec->material = cone->material;
	return (1);
}
