/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 16:18:10 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/28 09:47:42 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_camera_params		cam_default_params(void)
{
	return ((t_camera_params) {
			.pos = CAM_DEFAULT_POS,
			.up = CAM_DEFAULT_UP,
			.lookat = CAM_DEFAULT_LOOKAT,
			.light = CAM_DEFAULT_LIGHT
			});
}

t_material			sphere_default_material(void)
{
	return ((t_material) {
			.type = LAMBERTIAN,
			.color = (t_v3){255.0f, .0f, .0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .9f
			});
}

t_material			cylinder_default_material(void)
{
	return ((t_material) {
			.type = LAMBERTIAN,
			.color = (t_v3){0.0f, 122.0f, 122.0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .0f
			});
}

t_material			plane_default_material(void)
{
	return ((t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){122.0f, 122.0f, 122.0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .0f
			});
}

t_material			cone_default_material(void)
{
	return ((t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){122.0f, 0.0f, 122.0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .6f
			});
}
