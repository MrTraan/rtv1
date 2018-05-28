/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 17:17:00 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/24 16:11:34 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <float.h>

t_v3		hit_skybox(t_ray r)
{
	float		t;
	t_v3		unit_direction;
	t_v3		color;

	unit_direction = v3_unit(r.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	color = v3_add(v3_mul_float((t_v3){1.0, 1.0, 1.0}, 1.0 - t),
			v3_mul_float((t_v3){0.5, 0.7, 1.0}, t));
	return (v3_mul_float(color, 255));
}

t_v3		phong_shading(t_app *app, t_hit_record hit, t_ray ray)
{
	float	angle;
	float	specular_factor;
	float	d;
	t_v3	l;

	l = v3_unit(v3_sub(app->camera.light, hit.p));
	angle = v3_dot(v3_unit(hit.normal), l);
	if (angle < 0)
		return (v3_mul_float(hit.material.color, hit.material.ambiant));
	d = v3_dot(v3_unit(ray.direction),
			v3_sub(l, v3_mul_float(hit.normal, 2 * angle)));
	if (d > 0)
		specular_factor = pow(d, 50) * hit.material.specular;
	else
		specular_factor = 0;
	return (v3_add(v3_add(
		v3_mul_float(hit.material.color, hit.material.ambiant),
		v3_mul_float(hit.material.color, angle * hit.material.diffuse)),
		v3_mul_float(LIGHT_COLOR, specular_factor)));
}

char		hit_is_shaded(t_app *app, t_hit_record rec, t_list *hitable_list)
{
	t_ray				r;
	t_hit_record		temp_record;
	t_list				*iter;

	r.origin = rec.p;
	r.direction = app->camera.light;
	if (r.direction.x == 0 && r.direction.y == 0 && r.direction.z == 0)
		r.direction.z -= 0.0001;
	iter = hitable_list;
	while (iter)
	{
		if (iter == rec.item_hit)
		{
			iter = iter->next;
			continue ;
		}
		if (ray_hit(r, (t_hitable *)iter->content, (t_v2){0.01,
					v3_length(v3_sub(rec.p, app->camera.light))}, &temp_record))
			return (1);
		iter = iter->next;
	}
	return (0);
}

t_v3		compute_ray_color(t_app *app, t_ray r, t_list *hitable_list)
{
	t_hit_record rec;

	if (!ray_hit_list(r, hitable_list, (t_v2){0.01, FLT_MAX}, &rec))
		return (hit_skybox(r));
	if (hit_is_shaded(app, rec, hitable_list))
		return (v3_mul_float(rec.material.color, rec.material.ambiant));
	return (phong_shading(app, rec, r));
}
