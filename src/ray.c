/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:34:45 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/17 19:16:07 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <float.h>

t_v3		ray_point_at_parameter(t_ray r, float t)
{
	t_v3	res;

	res = (t_v3){
		.x = r.origin.x + t * r.direction.x,
		.y = r.origin.y + t * r.direction.y,
		.z = r.origin.z + t * r.direction.z
	};
	return (res);
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

char	ray_hit(t_ray r, t_hitable *hitable, t_v2 boundaries, t_hit_record *rec)
{
	if (hitable->type == SPHERE)
		return ray_hit_sphere((t_sphere *)hitable, r, boundaries, rec);
	return (0);
}

char	ray_hit_list(t_ray r, t_list *hitable_list, t_v2 boundaries, t_hit_record *rec)
{
	t_hit_record		temp_record;
	char				hit_anything;
	t_list				*iter;

	hit_anything = 0;
	iter = hitable_list;
	while (iter)
	{
		if (ray_hit(r, (t_hitable *)iter->content, boundaries, &temp_record))
		{
			hit_anything = 1;
			boundaries.y = temp_record.t;
			ft_memcpy(rec, &temp_record, sizeof(t_hit_record));
		}
		iter = iter->next;
	}
	return (hit_anything);
}

t_v3		phong_shading(t_app *app, t_hit_record hit, t_ray ray)
{
	float angle;

	angle = TO_RADIAN(v3_dot(hit.normal, app->camera.light));

	float specular_factor = 0.0f;
	float d = v3_dot(hit.normal, app->camera.light);
	d = v3_dot(v3_unit(ray.direction), v3_sub(app->camera.light, v3_mul_float(hit.normal, 2.0 * d)));
	if (d > 0)
		specular_factor = pow(d, SPECULAR_POW);

	return (v3_add(v3_add(
		v3_mul_float(hit.material.color, angle * hit.material.diffuse),
		v3_mul_float(hit.material.color, hit.material.ambiant)),
		v3_mul_float(hit.material.color, hit.material.specular * specular_factor)
	));
}

t_v3		compute_ray_color(t_app *app, t_ray r, t_list *hitable_list)
{
	t_hit_record rec;

	if (!ray_hit_list(r, hitable_list, (t_v2){0.01, FLT_MAX}, &rec))
		return ((t_v3){0, 0, 0});
	return (phong_shading(app, rec, r));
}
