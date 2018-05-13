/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:34:45 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/13 13:24:22 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <float.h>
#include <stdio.h>

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

t_v3		hit_skybox(t_ray r)
{
	float	t;
	t_v3	unit_direction;

	unit_direction = v3_unit(r.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	t_v3 color = v3_add(v3_mul_float((t_v3){1.0, 1.0, 1.0}, 1.0 - t), v3_mul_float((t_v3){0.5, 0.7, 1.0}, t));
	return (v3_mul_float(color, 255));
}


char	ray_hit(t_ray r, t_hitable *hitable, t_v2 boundaries, t_hit_record *rec)
{
	if (hitable->type == SPHERE)
		return ray_hit_sphere((t_sphere *)hitable, r, boundaries, rec);
	if (hitable->type == PLANE)
		return ray_hit_plane((t_plane *)hitable, r, boundaries, rec);
	if (hitable->type == CYLINDER)
		return ray_hit_cylinder((t_cylinder *)hitable, r, boundaries, rec);
	if (hitable->type == CONE)
		return ray_hit_cone((t_cone *)hitable, r, boundaries, rec);
	return (0);
}

char	ray_hit_list(t_ray r, t_list *hitable_list, t_v2 boundaries, t_hit_record *rec)
{
	t_hit_record		temp_record;
	char				hit_anything;
	t_list				*iter;

	hit_anything = 0;
	iter = hitable_list;
	rec->item_hit = NULL;
	while (iter)
	{
		if (ray_hit(r, (t_hitable *)iter->content, boundaries, &temp_record))
		{
			hit_anything = 1;
			boundaries.y = temp_record.t;
			temp_record.item_hit = iter;
			ft_memcpy(rec, &temp_record, sizeof(t_hit_record));
		}
		iter = iter->next;
	}
	return (hit_anything);
}

t_v3		phong_shading(t_app *app, t_hit_record hit, t_ray ray)
{
	float angle;
	float specular_factor;

	t_v3 l = v3_unit(v3_sub(app->camera.light, hit.p));
	angle = v3_dot(v3_unit(hit.normal), l);

	if (angle < 0)
		return (v3_mul_float(hit.material.color, hit.material.ambiant));

	float d = v3_dot(v3_unit(ray.direction), v3_sub(l, v3_mul_float(hit.normal, 2 * angle)));

	if (d > 0)
		specular_factor = pow(d, 50) * hit.material.specular;
	else
		specular_factor = 0;

	return (v3_add(v3_add(
		v3_mul_float(hit.material.color, hit.material.ambiant),
		v3_mul_float(hit.material.color, angle * hit.material.diffuse)),
		v3_mul_float(LIGHT_COLOR, specular_factor)
	));
}

char		hit_is_shaded(t_app *app, t_hit_record rec, t_list *hitable_list)
{
	t_ray				r;
	t_hit_record		temp_record;
	t_list				*iter;

	r.origin = rec.p;
	r.direction = app->camera.light;
	iter = hitable_list;
	while (iter)
	{
		if (iter == rec.item_hit)
		{
			iter = iter->next;
			continue ;
		}
		if (ray_hit(r, (t_hitable *)iter->content, (t_v2){0.01, FLT_MAX}, &temp_record))
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
