/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:04:20 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/23 16:36:39 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_v3		cylinder_normal(t_cylinder *cylinder, t_v3 e, t_v3 d, double t)
{
	double		invr;
	t_v3		normal;

	invr = 1.0 / (cylinder->radius * cylinder->radius);
	normal = (t_v3){(e.x + d.x * t) * invr, 0, (e.z + d.z * t) * invr};
	normal = v3_rot(normal, cylinder->direction);
	return (v3_unit(normal));
}

char		ray_hit_cylinder(t_cylinder *cylinder, t_ray ray,
				t_v2 t_min_max, t_hit_record *rec)
{
	t_v3		p;
	t_v3		e;
	t_v3		d;

	e = v3_rot(v3_sub(ray.origin, cylinder->origin),
			v3_reverse(cylinder->direction));
	d = v3_rot(ray.direction, v3_reverse(cylinder->direction));
	p.x = (d.x * d.x) + (d.z * d.z);
	p.y = 2.0 * (e.x * d.x + e.z * d.z);
	p.z = (e.x * e.x) + (e.z * e.z) - (cylinder->radius * cylinder->radius);
	if (find_roots(p, t_min_max, &(rec->t)) == 0)
		return (0);
	rec->p = ray_point_at_parameter(ray, rec->t);
	rec->normal = cylinder_normal(cylinder, e, d, rec->t);
	rec->material = cylinder->material;
	return (1);
}
