/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:34:45 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/23 17:23:19 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_v3	ray_point_at_parameter(t_ray r, float t)
{
	t_v3	res;

	res = (t_v3){
		.x = r.origin.x + t * r.direction.x,
		.y = r.origin.y + t * r.direction.y,
		.z = r.origin.z + t * r.direction.z
	};
	return (res);
}

char	ray_hit(t_ray r, t_hitable *hitable, t_v2 boundaries, t_hit_record *rec)
{
	if (hitable->type == SPHERE)
		return (ray_hit_sphere((t_sphere *)hitable, r, boundaries, rec));
	if (hitable->type == PLANE)
		return (ray_hit_plane((t_plane *)hitable, r, boundaries, rec));
	if (hitable->type == CYLINDER)
		return (ray_hit_cylinder((t_cylinder *)hitable, r, boundaries, rec));
	if (hitable->type == CONE)
		return (ray_hit_cone((t_cone *)hitable, r, boundaries, rec));
	return (0);
}

char	ray_hit_list(t_ray r, t_list *hitable_list, t_v2 boundaries,
			t_hit_record *rec)
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
