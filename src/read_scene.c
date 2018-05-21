/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 15:57:53 by dbousque          #+#    #+#             */
/*   Updated: 2018/05/21 16:18:53 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_default_scene(t_app *app)
{
	t_list	*hitable_list;

	hitable_list = NULL;
	t_sphere s = {
		.type = SPHERE,
		.center = (t_v3){-2.5f, -2.5f, .0f},
		.radius = .3f,
		.material = (t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){255.0f, .0f, .0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .9f
		}
	};

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			s.center.y += 0.7f;
			/* ft_lstpush_back(&hitable_list, ft_lstnew(&s, sizeof(t_sphere))); */
		}
		s.center.y = -2.5f;
		s.center.x += 0.7f;
	}
	
	t_sphere sl = {
		.type = SPHERE,
		.center = app->camera.light,
		.radius = .05f,
		.material = (t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){255.0f, .0f, .0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .9f
		}
	};
	ft_lstpush_back(&hitable_list, ft_lstnew(&sl, sizeof(t_sphere)));

	t_plane p = {
		.type = PLANE,
		.origin = (t_v3){.0f, .0f, -2.0f},
		.normal = (t_v3){.0f, .0f, 1.f},
		.material = (t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){122.0f, 122.0f, 122.0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .0f
		}
	};
	ft_lstpush_back(&hitable_list, ft_lstnew(&p, sizeof(t_plane)));
	(void)p;
	
	t_cylinder cylinder = {
		.type = CYLINDER,
		.origin = (t_v3){2.0f, .0f, -1.0f},
		.direction = (t_v3){.0f, 1.0f, .0f},
		.radius = .6f,
		.material = (t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){.0f, 122.0f, .0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .1f
		}
	};
	ft_lstpush_back(&hitable_list, ft_lstnew(&cylinder, sizeof(t_cylinder)));
	(void)cylinder;

	t_cone cone = {
		.type = CONE,
		.origin = (t_v3){0.0f, .0f, -1.0f},
		.direction = v3_unit((t_v3){0.5, 1, 0}),
		.alpha = TO_RADIAN(45),
		.material = (t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){.0f, 122.0f, .0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .9f
		}
	};
	ft_lstpush_back(&hitable_list, ft_lstnew(&cone, sizeof(t_cone)));

	app->hitable_list = hitable_list;
}

char	*read_error(char *error, char err, char *contents)
{
	if (contents)
		free(contents);
	*error = err;
	return (NULL);
}

char	*read_whole_file(char *filename, char *error, int max_size)
{
	char	*res;
	char	buf[1024];
	int		s;
	int		ret;
	int		fd;

	*error = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (read_error(error, 1, NULL));
	s = 0;
	while ((ret = read(fd, buf, 1024)) > 0)
	{
		s += ret;
		if (s > max_size)
			return (read_error(error, 3, NULL));
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (read_error(error, 1, NULL));
	if (!(res = (char*)malloc(sizeof(char) * (s + 1))) || read(fd, res, s) < 0)
		return (read_error(error, 2, res));
	res[s] = '\0';
	return (res);
}
#include <stdio.h>
int		parse_camera(t_app *app, char *data)
{
	t_v3	pos;
	t_v3	up;
	t_v3	lookat;
	t_v3 	light;
	int 	offset;

	pos = CAM_DEFAULT_POS;
	up = CAM_DEFAULT_UP;
	lookat = CAM_DEFAULT_LOOKAT;
	light = CAM_DEFAULT_LIGHT;
	offset = 0;
	while (data[offset] && data[offset + 1] != '-')
	{
		if (ft_strncmp("-pos ", data + offset, 5) == 0)
		{
			int matches = sscanf(data + offset, "-pos %f %f %f\n", &(pos.x), &(pos.y), &(pos.z));
			if (matches != 3)
				break;
			printf("1: %d\n", offset);
			if (!ft_strchr(data + offset, '\n'))
				break;
			printf("remaining: ||%s||\n", ft_strchr(data + offset, '\n'));
			offset = ft_strchr(data + offset, '\n') - data + 1;
			printf("2: %d\n", offset);
		}
		else if (ft_strncmp("-up ", data + offset, 4) == 0)
		{
			int matches = sscanf(data + offset, "-up %f %f %f\n", &(up.x), &(up.y), &(up.z));
			if (matches != 3)
				break;
			if (!ft_strchr(data + offset, '\n'))
				break;
			printf("1: %d\n", offset);
			printf("remaining: ||%s||\n", ft_strchr(data + offset, '\n'));
			offset = ft_strchr(data + offset, '\n') - data + 1;
			printf("2: %d\n", offset);
		}
		else if (ft_strncmp("-lookat ", data + offset, 8) == 0)
		{
			int matches = sscanf(data + offset, "-lookat %f %f %f\n", &(lookat.x), &(lookat.y), &(lookat.z));
			if (matches != 3)
				break;
			if (!ft_strchr(data + offset, '\n'))
				break;
			offset += ft_strchr(data + offset, '\n') - data + offset + 1;
		}
		else if (ft_strncmp("-light ", data + offset, 7) == 0)
		{
			int matches = sscanf(data + offset, "-light %f %f %f\n", &(lookat.x), &(lookat.y), &(lookat.z));
			if (matches != 3)
				break;
			if (!ft_strchr(data + offset, '\n'))
				break;
			offset += ft_strchr(data + offset, '\n') - data + offset + 1;
		}
		else
			break ;
	}
	camera_init(&(app->camera), pos, up, lookat, light);
	return (offset);
}

void	interpret_scene_file(t_app *app, char *data)
{
	while (*data)
	{
		if (ft_strncmp("--camera\n", data, 9) == 0)
		{
			data += 9 + parse_camera(app, data + 9);
			printf("remaining: ||%s||", data);
		}
		else
		{
			printf("Invalid instruction\n");
			data = ft_strchr(data, '\n');
			if (data)
				data++;
		}
	}
}

void	read_scene(t_app *app, int argc, char **argv)
{
	char	*file_contents;
	char	error;

	app->hitable_list = NULL;
	if (argc < 2)
	{
		ft_putstr("No scene to load\n");
		ft_putstr("Usage : ./rtv1 [scene_file]\n");
		set_default_scene(app);
		return ;
	}
	if (!(file_contents = read_whole_file(argv[1], &error, 3 * 1024 * 1024)))
	{
		if (error == 1)
			ft_putstr("Could not open scene file\n");
		if (error == 2)
			ft_putstr("Could not read scene file\n");
		if (error == 3)
			ft_putstr("Scene file is too big, must be <= 3MB\n");
		return ;
	}
	interpret_scene_file(app, file_contents);
}
