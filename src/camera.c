/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:39:26 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/18 00:29:43 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		camera_init(t_camera *cam)
{
	float	half_height;
	float	half_width;

	half_height = tan(CAMERA_THETA / 2);
	half_width = WIN_WIDTH / WIN_HEIGHT * half_height;
	cam->lookfrom = (t_v3){.0f, 0.0f, 15.0f};
	cam->lookat = (t_v3){0.0f, 0.0f, 0.0f};
	cam->up = (t_v3){0.0f, 1.0f, 0.0f};
	cam->w = v3_unit(v3_sub(cam->lookfrom, cam->lookat));
	cam->u = v3_unit(v3_cross(cam->up, cam->w));
	cam->v = v3_cross(cam->w, cam->u);
	// lower_left_corner = lookfrom - half_width * focus_dist * u - half_height * focus_dist * v - w
	cam->lower_left_corner = v3_sub(v3_sub(v3_sub(
			cam->lookfrom,
			v3_mul_float(cam->u, half_width * CAMERA_FOCUS_DIST)),
			v3_mul_float(cam->v, half_height * CAMERA_FOCUS_DIST)),
			v3_mul_float(cam->w, CAMERA_FOCUS_DIST));
	cam->horizontal = v3_mul_float(cam->u, 2 * half_width * CAMERA_FOCUS_DIST);
	cam->vertical = v3_mul_float(cam->v, 2 * half_height * CAMERA_FOCUS_DIST);
	cam->origin = cam->lookfrom;
	cam->light = (t_v3){-5.0f, 4.0f, 10.0f};
}

t_ray		camera_get_ray(t_camera *cam, t_iv2 point)
{
	t_ray	r;
	float	u;
	float	v;

	u = (float)point.x / (float)WIN_WIDTH;
	v = (float)point.y / (float)WIN_HEIGHT;
	r.origin = cam->origin;
	r.direction = (t_v3) {
		.x = cam->lower_left_corner.x + u * cam->horizontal.x + v * cam->vertical.x - cam->origin.x,
		.y = cam->lower_left_corner.y + u * cam->horizontal.y + v * cam->vertical.y - cam->origin.y,
		.z = cam->lower_left_corner.z + u * cam->horizontal.z + v * cam->vertical.z - cam->origin.z,
	};
	return (r);
}

t_ray		camera_get_uv_ray(t_camera *cam, float u, float v)
{
	t_ray	r;

	r.origin = cam->origin;
	r.direction = (t_v3) {
		.x = cam->lower_left_corner.x + u * cam->horizontal.x + v * cam->vertical.x - cam->origin.x,
		.y = cam->lower_left_corner.y + u * cam->horizontal.y + v * cam->vertical.y - cam->origin.y,
		.z = cam->lower_left_corner.z + u * cam->horizontal.z + v * cam->vertical.z - cam->origin.z,
	};
	return (r);
}
