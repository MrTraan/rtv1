/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 23:57:07 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/23 16:35:50 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

char		ray_hit_plane(t_plane *plane, t_ray ray, t_v2 t_min_max,
				t_hit_record *rec)
{
	float		n;
	float		d;
	float		dist;

	n = v3_dot(plane->normal, v3_sub(plane->origin, ray.origin));
	d = v3_dot(plane->normal, ray.direction);
	dist = n / d;
	if (dist > t_min_max.x && dist < t_min_max.y)
	{
		rec->t = dist;
		rec->p = ray_point_at_parameter(ray, dist);
		rec->normal = plane->normal;
		rec->material = plane->material;
		return (1);
	}
	return (0);
}

char	ray_hit_sphere(t_sphere *sphere, t_ray r, t_v2 t_min_max,
			t_hit_record *rec)
{
	t_v3	oc;
	t_v3	p;

	oc = v3_sub(r.origin, sphere->center);
	p.x = v3_dot(r.direction, r.direction);
	p.y = 2.0 * v3_dot(oc, r.direction);
	p.z = v3_dot(oc, oc) - sphere->radius * sphere->radius;
	if ((find_roots(p, t_min_max, &(rec->t))) == 0)
		return (0);
	rec->p = ray_point_at_parameter(r, rec->t);
	rec->normal = v3_mul_float(v3_sub(rec->p, sphere->center), 1.0 / sphere->radius);
	rec->material = sphere->material;
	return (1);
}
