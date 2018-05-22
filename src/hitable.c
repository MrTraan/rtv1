/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 23:57:07 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/22 11:34:06 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_v3		cylinder_normal(t_cylinder *cylinder, t_v3 e, t_v3 d, double t)
{
	double		invr;
	t_v3		normal;

	invr = 1.0 / (cylinder->radius * cylinder->radius);
	normal = (t_v3){(e.x + d.x * t) * invr, 0, (e.z + d.z * t) * invr};
	normal = rotate(normal, cylinder->direction);
	return (v3_unit(normal));

}

char		ray_hit_cylinder(t_cylinder *cylinder, t_ray ray, t_v2 t_min_max, t_hit_record *rec)
{
	float		discriminant;
	float 		temp;
	t_v3		v;
	t_v3		e;
	t_v3		d;

	e = rotate(v3_sub(ray.origin, cylinder->origin), v3_reverse(cylinder->direction));
	d = rotate(ray.direction, v3_reverse(cylinder->direction));
	v.x = (d.x * d.x) + (d.z * d.z);
	v.y = 2.0 * (e.x * d.x + e.z * d.z);
	v.z = (e.x * e.x) + (e.z * e.z) - (cylinder->radius * cylinder->radius);
	discriminant = (v.y * v.y) - (4.0 * v.x * v.z);
	if (discriminant < 0)
		return (0);
	temp = ((-v.y - sqrt(discriminant)) / (2.0 * v.x));
	if (temp < t_min_max.x || temp > t_min_max.y)
		temp = ((-v.y + sqrt(discriminant)) / (2.0 * v.x));
	if (temp < t_min_max.x || temp > t_min_max.y)
		return (0);
	rec->t = temp;
	rec->p = ray_point_at_parameter(ray, temp);	
	rec->normal = cylinder_normal(cylinder, e, d, temp);
	rec->material = cylinder->material;
	return (1);
}

char		ray_hit_plane(t_plane *plane, t_ray ray, t_v2 t_min_max, t_hit_record *rec)
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

char	ray_hit_sphere(t_sphere *sphere, t_ray r, t_v2 t_min_max, t_hit_record *rec)
{
	t_v3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	temp;

	oc = v3_sub(r.origin, sphere->center);
	a = v3_dot(r.direction, r.direction);
	b = 2.0 * v3_dot(oc, r.direction);
	c = v3_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	temp = ((-b - sqrt(discriminant)) / (2.0 * a));
	if (temp < t_min_max.x || temp > t_min_max.y)
		temp = ((-b + sqrt(discriminant)) / (2.0 * a));
	if (temp < t_min_max.x || temp > t_min_max.y)
		return (0);
	rec->t = temp;
	rec->p = ray_point_at_parameter(r, temp);
	rec->normal = v3_mul_float(v3_sub(rec->p, sphere->center), 1.0 / sphere->radius);
	rec->material = sphere->material;
	return (1);
}
