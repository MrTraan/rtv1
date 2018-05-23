/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:26:09 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/23 16:21:21 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

char			ray_hit_cone(t_cone *cone, t_ray ray, t_v2 t_min_max,
					t_hit_record *rec)
{
	t_v3		p;
	t_v3		rc;
	t_v3		d;
	t_v3		x;
	float		k;

	k = tan(cone->alpha / 2);
	d = ray.direction;
	rc = v3_sub(ray.origin, cone->origin);
	x = v3_sub(ray.origin, cone->origin);
	p.x = v3_dot(d, d) - (1 + k * k) * pow(v3_dot(d, cone->direction), 2);
	p.y = 2 * (v3_dot(d, x) - (1 + k * k) * v3_dot(d, cone->direction) *
			v3_dot(x, cone->direction));
	p.z = v3_dot(x, x) - (1 + k * k) * pow(v3_dot(x, cone->direction), 2);
	if (find_roots(p, t_min_max, &(rec->t)) == 0)
		return (0);
	rec->p = ray_point_at_parameter(ray, rec->t);
	rec->normal = v3_unit(v3_sub(
			v3_sub(rec->p, cone->origin),
			v3_mul_float(cone->direction, (1 + k * k) *
			(v3_dot(ray.direction, v3_mul_float(cone->direction, rec->t)) +
			v3_dot(rc, cone->direction)))));
	rec->material = cone->material;
	return (1);
}
